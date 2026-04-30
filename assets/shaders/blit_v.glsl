#version 330 core
const vec2 pos[4] = vec2[](vec2(-1, -1), vec2(1, -1), vec2(-1, 1), vec2(1, 1));
const vec2 uvs[4] = vec2[](vec2(0, 0), vec2(1, 0), vec2(0, 1), vec2(1, 1));

out vec2 uv;

void main()
{
    gl_Position = vec4(pos[gl_VertexID], 0, 1);
    uv = uvs[gl_VertexID];
}