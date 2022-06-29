#version 430

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec3 vertex_normal;

uniform mat4 mvp;
uniform float scale;

uniform mat4 light_mvp;

out VERTEX_OUT {
    vec4 positionLightSpace;
    vec2 uv;
} vertex_out;

void main()
{
    vec3 position = vertex_position;
    vertex_out.uv = vertex_uv * scale;
    vertex_out.positionLightSpace = light_mvp * vec4(position, 1);
    gl_Position = mvp * vec4(position, 1.0);
}