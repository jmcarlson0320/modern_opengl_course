#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 tex_coor;

out vec3 frag_pos;
out vec3 vertex_normal;
out vec2 vertex_texture_coor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0f);

    frag_pos = (model * vec4(pos, 1.0f)).xyz;
    vertex_normal = mat3(transpose(inverse(model))) * normal;
    vertex_texture_coor = tex_coor;
}
