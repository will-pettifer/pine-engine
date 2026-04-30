#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

#define MAX_LIGHTS 16
struct PointLight {
    vec3 position;
    vec3 colour;
    float intensity;
    float radius;
};
uniform int numPLights;
uniform PointLight pointLights[MAX_LIGHTS];

// Directional light
struct DirectionalLight {
    bool enabled;
    vec3 direction;
    vec3 colour;
    float intensity;
};
uniform DirectionalLight dLight;

out vec3 vertexColour;
noperspective out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    vec3 normal = normalize(mat3(transpose(inverse(model))) * aNormal);

    TexCoords = aTexCoords;

    gl_Position = projection * view * worldPos;
    gl_Position.xy = round(gl_Position.xy * 10) / 10;

    vec3 lighting = vec3(0.3);

    if (dLight.enabled) {
        vec3 lightDir = normalize(-dLight.direction);
        float diffuse = max(dot(normal, lightDir), 0.0);
        lighting += dLight.colour * diffuse * dLight.intensity;
    }

    for (int i = 0; i < numPLights; i++) {
        vec3 lightDir = normalize(pointLights[i].position - vec3(worldPos));
        float diffuse = max(dot(normal, lightDir), 0.0);

        float dist = length(pointLights[i].position - vec3(worldPos));
        float attenuation = clamp(1.0 - dist / pointLights[i].radius, 0.0, 1.0);

        lighting += pointLights[i].colour * diffuse * pointLights[i].intensity * attenuation;
    }

    vertexColour = lighting;
}