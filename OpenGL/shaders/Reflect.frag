#version 330 core

out vec4 FragColor;

struct Material {
    float shininess;
}; 

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

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;
uniform DirectionalLight light;
uniform vec3 viewPos;
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform samplerCube skybox;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

vec3 computeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 I, vec3 R) {
	vec3 lightDir = normalize(-light.direction);

	float diffuseFact = max(dot(normal, lightDir), 0.0);

	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularFact = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);
	
	vec3 ambient = light.ambient * vec3(texture(diffuseMap, texCoords));
	vec3 diffuse = light.diffuse * diffuseFact * vec3(texture(diffuseMap, texCoords));
	vec3 specular = light.specular * specularFact * vec3(texture(specularMap, texCoords));
	//vec3 specular = vec3(texture(specularMap, texCoords)) * texture(skybox, R).rgb;
	return (specular + ambient + diffuse);
}

vec3 computePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	float diffuseFact = max(dot(normal, lightDir), 0.0);

	vec3 reflectionDir = reflect(-lightDir, normal);
	float specularFact = pow(max(dot(viewDir, reflectionDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(diffuseMap, texCoords)) * attenuation;
	vec3 diffuse = light.diffuse * diffuseFact * vec3(texture(diffuseMap, texCoords)) * attenuation;
	vec3 specular = light.specular * specularFact * vec3(texture(specularMap, texCoords)) * attenuation;
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 normalizedNorm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 I = normalize(fragPos - viewPos);
	vec3 R = reflect(I, normalize(normal));

	vec3 result = computeDirectionalLight(light, normalizedNorm, viewDir, I, R);


	for(int i=0; i< NR_POINT_LIGHTS; i++) {
		result += computePointLight(pointLights[i], normalizedNorm, fragPos, viewDir);
	}
	
	FragColor = vec4(result, 1.0);
}