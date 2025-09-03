#version 410

in vec4 fragColor;
in vec2 fragPosTex;
flat in float fragTexId;

out vec4 finalColor;

uniform sampler2D uTexture[2];

void main()
{
//	int index = int(fragTexId);
//	finalColor = texture(uTexture[index], fragPosTex);
	finalColor = fragColor;
}
