#version 330

in vec3 vertex_normal;
in vec3 vertex_color;
in vec2 vertex_texture_coor;

out vec4 color;

void main()
{
    color = vec4(vertex_color, 1.0f);
}
