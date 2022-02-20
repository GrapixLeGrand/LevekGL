#version 430

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_uv;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in vec3 world_position;

uniform mat4 vp; //only view projection, m is the I matrix

out vec3 normal;
//out vec3 v2f_position;


void main()
{
    normal = vertex_normal;
    gl_Position = vp * vec4(vertex_position + world_position, 1.0); 
}