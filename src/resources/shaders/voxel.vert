#version 430

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in vec3 offset;
layout (location = 4) in uint palette_index;


out VERTEX_OUT {
    vec3 normalView;
    vec3 positionView;
    vec2 uv;
} vertex_out;

flat out uint palette_index_v2f;

uniform mat4 vp;
uniform float scale;

void main()
{
    vertex_out.uv = vertex_uv;
    palette_index_v2f = palette_index;
    //vertex_out.normalView = normalize(normal_view * vertex_normal);
    gl_Position = vp * vec4(vertex_position * scale + offset, 1.0);
}