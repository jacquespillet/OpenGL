#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D hdrBuffer;
uniform sampler2D bloom;
uniform float exposure;

void main()
{        
	const float gamma = 2.2;
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
	vec3 bloomColor = texture(bloom, TexCoords).rgb;
    hdrColor += bloomColor;

	vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
	mapped = pow(mapped, vec3(1.0 / gamma));

	FragColor = vec4(mapped, 1.0);
}