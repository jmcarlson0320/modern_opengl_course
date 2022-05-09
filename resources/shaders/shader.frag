#version 330

in vec3 vertex_color;
in vec2 vertex_texture_coor;

out vec4 color;

uniform sampler2D theTexture;

void main()
{
        color = texture(theTexture, vertex_texture_coor);
}
