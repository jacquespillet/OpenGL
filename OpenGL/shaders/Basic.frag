#version 330 core

out vec4 FragColor;
in vec4 position; 
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float texRatio;

void main()
{
	vec2 newTex = texCoord;
	newTex.x = 1.0 - newTex.x;
   FragColor = mix(texture(ourTexture, newTex), texture(ourTexture2, newTex), texRatio);
}