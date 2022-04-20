#version 330

in vec2 vertex_tex_coor;

out vec4 color;

void main()
{
	color = vec4(vertex_tex_coor.x, vertex_tex_coor.y, 0.8f, 1.0f);
}
