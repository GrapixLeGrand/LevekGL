#version 430

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in vec3 world_position;

uniform mat4 vp; //only view projection, m is the I matrix
uniform mat4 view;
uniform mat4 p;
uniform mat4 v;
uniform mat3 view_inv;

out vec3 v2f_normal;
out vec2 v2f_uv;
out vec3 v2f_position_view;
//out vec3 v2f_position;

void main()
{
    v2f_uv = vertex_uv;
    v2f_normal = vertex_normal;
    vec4 temp = v * vec4(world_position, 1.0);
    v2f_position_view = temp.xyz / temp.w;

    vec3 pos = view_inv * vertex_position + world_position;

    gl_Position = vp * vec4(pos, 1.0);
}