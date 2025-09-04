#version 410

in vec4 fragColor;
in vec2 fragPosTex;
flat in float fragTexId;

out vec4 finalColor;

uniform sampler2D texture_diffuse1;

void main()
{
	finalColor = texture(texture_diffuse1, fragPosTex);
}
