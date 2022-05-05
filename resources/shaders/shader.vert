#version 330

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Color;

out vec3 vColor;

uniform mat4 projection;

void main()
{
	vColor = in_Color;
	gl_Position = projection * vec4(in_Position, 1.0f);
}
