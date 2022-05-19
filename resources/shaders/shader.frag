#version 330

in vec3 vertex_color;
in vec2 vertex_texture_coor;
in vec3 vertex_normal;
in vec3 frag_pos;

out vec4 color;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    vec3 direction;
    float diffuseIntensity;
};

struct Material
{
    float specular_intensity;
    float shininess;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eye;

void main()
{
        vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;

        float diffuseFactor = max(dot(normalize(vertex_normal), normalize(directionalLight.direction)), 0.0f);
        vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

        vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

        if (diffuseFactor > 0.0f) {
            vec3 fragToEye = normalize(eye - frag_pos);
            vec3 reflection = normalize(reflect(directionalLight.direction, normalize(vertex_normal)));
            float specularFactor = dot(fragToEye, reflection);
            if (specularFactor > 0.0f) {
                specularFactor = pow(specularFactor, material.shininess);
                specularColor = vec4((directionalLight.color * material.specular_intensity * specularFactor), 1.0f);
            }
        }

        color = texture(theTexture, vertex_texture_coor) * (ambientColor + diffuseColor + specularColor);
}
