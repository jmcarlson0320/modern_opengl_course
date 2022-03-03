#version 330

layout (location = 0) in vec3 pos;

uniform float x_move;

void main()
{
	gl_Position = vec4(pos.x + x_move, pos.y, pos.z, 1.0f);
}
