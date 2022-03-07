#version 330

layout (location = 0) in vec3 pos;

out vec4 vertex_color;

uniform mat4 model;

void main()
{
	gl_Position = model * vec4(pos.x, pos.y, pos.z, 1.0f);
    vertex_color = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}
