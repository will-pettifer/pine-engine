#version 330 core
out vec4 FragColor;

noperspective in vec2 TexCoords;

uniform sampler2D albedo;

const mat4 bayer = mat4(
-4, 0, -3, 1,
2, -2, 3, -1,
-3, 1, -4, 0,
3, -1, 2, -2
) / 8;

void main()
{
    vec4 colour = texture(albedo, TexCoords);

    ivec2 pos = ivec2(gl_FragCoord.xy) % 4;
    float threshold = bayer[pos.x][pos.y];

    colour.rgb += threshold / 31;
    colour.rgb = floor(colour.rgb * 31) / 31;

    FragColor = colour;
}