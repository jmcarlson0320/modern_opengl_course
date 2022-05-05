#version 330

layout (location = 0) out vec4 out_fragmentColor;

in vec3 vColor;

void main()
{
    out_fragmentColor = vec4(vColor, 1.0);
}
