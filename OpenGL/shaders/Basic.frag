#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D boxTexture;

void main()
{
	vec4 texColor = texture(boxTexture, texCoord);
	if(texColor.a < 0.1) 
		discard;
	FragColor = texColor;
}