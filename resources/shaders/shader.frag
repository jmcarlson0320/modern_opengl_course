#version 330

in vec3 vertex_color;
in vec2 vertex_texture_coor;
in vec3 vertex_normal;

out vec4 color;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
        vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

        float diffuseFactor = max(dot(normalize(vertex_normal), normalize(directionalLight.direction)), 0.0f);
        vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

        color = texture(theTexture, vertex_texture_coor) * (ambientColor + diffuseColor);
}
