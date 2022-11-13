#version 410 core

in vec3 frag_pos;
in vec3 vertex_normal;
in vec2 vertex_texture_coor;

out vec4 color;

// global properties
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float lightIntensity;
uniform float ambientIntensity;

// per object properties
uniform sampler2D theTexture;
uniform float specular_intensity;
uniform float shininess;
uniform vec3 eye;

void main()
{
    // calculate ambient term
    vec4 ambientColor = vec4(lightColor, 1.0f) * ambientIntensity;

    // calculate diffuse term
    vec3 lightDirection = lightPosition - frag_pos;
    float diffuseFactor = max(dot(normalize(vertex_normal), normalize(lightDirection)), 0.0f);
    vec4 diffuseColor = vec4(lightColor, 1.0f) * lightIntensity * diffuseFactor;

    // calculate specular term
    vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    if (diffuseFactor > 0.0f) {
        vec3 fragToEye = normalize(frag_pos - eye);
        vec3 reflection = normalize(reflect(lightDirection, normalize(vertex_normal)));
        float specularFactor = dot(fragToEye, reflection);
        if (specularFactor > 0.0f) {
            specularFactor = pow(specularFactor, shininess);
            specularColor = vec4((lightColor * specular_intensity * specularFactor), 1.0f);
        }
    }

    color = texture(theTexture, vertex_texture_coor) * (ambientColor + diffuseColor + specularColor);
}
