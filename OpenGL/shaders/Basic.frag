#version 330 core



struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 viewPos;
uniform DirectionalLight light;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 computeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);

	float diffuseFact = max(dot(normal, lightDir), 0.0);

	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularFact = pow(max(dot(viewDir, reflectionDir), 0.0), 0.8);

	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, texCoords));
	vec3 diffuse = light.diffuse * diffuseFact * vec3(texture(texture_diffuse1, texCoords));
	vec3 specular = light.specular * specularFact * vec3(texture(texture_specular1, texCoords));
	return (ambient + diffuse + specular);
}

vec3 computePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	float diffuseFact = max(dot(normal, lightDir), 0.0);

	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularFact = pow(max(dot(viewDir, reflectionDir), 0.0),0.8);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, texCoords)) * attenuation;
	vec3 diffuse = light.diffuse * diffuseFact * vec3(texture(texture_diffuse1, texCoords)) * attenuation;
	vec3 specular = light.specular * specularFact * vec3(texture(texture_specular1, texCoords)) * attenuation;
	return (ambient + diffuse + specular);
}

void main()
{    
	vec3 normalizedNorm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 result = computeDirectionalLight(light, normalizedNorm, viewDir);

	for(int i=0; i< NR_POINT_LIGHTS; i++) {
		result += computePointLight(pointLights[i], normalizedNorm, fragPos, viewDir);
	}

	FragColor = vec4(result, 1.0);
}