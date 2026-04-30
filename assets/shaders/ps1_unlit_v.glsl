#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

noperspective out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);

    TexCoords = aTexCoords;

    gl_Position = projection * view * worldPos;
    gl_Position.xy = round(gl_Position.xy * 10) / 10;
}