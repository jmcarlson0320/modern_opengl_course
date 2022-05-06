#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_coor;

out vec3 vertex_color;
out vec2 vertex_texture_coor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0f);
    vertex_color = color;
    vertex_texture_coor = tex_coor;
}
