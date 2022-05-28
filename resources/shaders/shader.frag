#version 330

in vec3 vertex_color;
in vec2 vertex_texture_coor;
in vec3 vertex_normal;
in vec3 frag_pos;

out vec4 color;

struct LightSource
{
    vec3 direction;
    float intensity;
    float ambientIntensity;
};

struct Material
{
    float specular_intensity;
    float shininess;
};

uniform sampler2D theTexture;
uniform LightSource light;

// flatten the LightSource struct
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform float lightIntensity;
uniform vec3 ambientColor;
uniform float ambientIntensity;

uniform Material material;

uniform vec3 eye;

void main()
{
        vec4 ambientColor = vec4(lightColor, 1.0f) * light.ambientIntensity;

        float diffuseFactor = max(dot(normalize(vertex_normal), normalize(light.direction)), 0.0f);
        vec4 diffuseColor = vec4(lightColor, 1.0f) * light.intensity * diffuseFactor;

        vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

        if (diffuseFactor > 0.0f) {
            vec3 fragToEye = normalize(eye - frag_pos);
            vec3 reflection = normalize(reflect(light.direction, normalize(vertex_normal)));
            float specularFactor = dot(fragToEye, reflection);
            if (specularFactor > 0.0f) {
                specularFactor = pow(specularFactor, material.shininess);
                specularColor = vec4((lightColor * material.specular_intensity * specularFactor), 1.0f);
            }
        }

        color = texture(theTexture, vertex_texture_coor) * (ambientColor + diffuseColor + specularColor);
}
