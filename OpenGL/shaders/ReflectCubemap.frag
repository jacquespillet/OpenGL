#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;
uniform sampler2D normals;
uniform sampler2D parallaxMap;

uniform float heightScale;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float far_plane;
uniform bool shadows;

vec2 parallaxMapping(vec2 texCoords, vec3 viewDir) {
	const float minLayers = 8.0;
	const float maxLayers = 32.0;
	float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
	float layerDepth = 1.0 / numLayers;

	float currentLayerDepth = 0.0;

	vec2 P = viewDir.xy * heightScale;
    vec2 deltaTexCoords = P / numLayers;

	vec2 currentTexCoords = texCoords;
	float currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;

	while(currentLayerDepth < currentDepthMapValue) {
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(parallaxMap, currentTexCoords).r;
		currentLayerDepth += layerDepth;
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(parallaxMap, prevTexCoords).r - currentLayerDepth + layerDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}

float ShadowCalculation(vec3 fragPos, vec3 lightDir, vec3 normal)
{
    vec3 fragToLight = fragPos - lightPos;
	float closestDepth = texture(depthMap, fragToLight).r;
	closestDepth *= far_plane;
	
	float currentDepth = length(fragToLight);

	float bias = 0.05;
	float samples = 4.0;
	float offset = 0.1;
	float shadow = 0.0;
	for(float x=-offset; x < offset; x+= offset / (samples * 0.5)) {
		for(float y=-offset; y < offset; y+= offset / (samples * 0.5)) {
			for(float z=-offset; z < offset; z+= offset / (samples * 0.5)) {
				float closestDepth = texture(depthMap, fragToLight + vec3(x, y, z)).r;
				closestDepth *= far_plane;
				if(currentDepth - bias > closestDepth)
					shadow += 1.0;
			}
		}	
	}
	shadow /= (samples * samples * samples);

	return shadow;
}

void main()
{           
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
	vec2 texCoords = parallaxMapping(fs_in.TexCoords, viewDir);
	if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		discard;

    vec3 color = texture(diffuseTexture, texCoords).rgb;
	vec3 normal = normalize(texture(normals, texCoords).rgb * 2.0 - 1.0);
    
    vec3 lightColor = vec3(0.3);

    vec3 ambient = 0.3 * color;

    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    

	float shadow = ShadowCalculation(fs_in.FragPos, lightDir, normal);                      

    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;    
    
    FragColor = vec4(lighting, 1.0);
}