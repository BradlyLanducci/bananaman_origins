#version 330 core
layout (location = 0) out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 healthTint = vec4(1.0);

void main()
{
	FragColor = healthTint * texture(texture1, TexCoord);
}