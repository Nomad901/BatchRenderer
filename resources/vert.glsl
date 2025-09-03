#version 410

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 posTex;
layout(location = 3) in float texID;

out vec4 fragColor;
out vec2 fragPosTex;
flat out float fragTexId;

uniform mat4 uMVP;

void main()
{
	gl_Position = uMVP * vec4(pos, 1.0);

	fragColor = color;
	fragPosTex = posTex;
	fragTexId = texID;
}

