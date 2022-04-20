#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coor;

out vec2 vertex_tex_coor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0f);

    vertex_tex_coor = tex_coor;
}
