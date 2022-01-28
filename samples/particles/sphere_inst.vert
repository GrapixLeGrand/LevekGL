#version 430

layout (location = 0) in vec3 sphere_vertex_position;
layout (location = 1) in vec3 position;

uniform mat4 vp; //only view projection, m is the I matrix

void main()
{
    gl_Position = vp * vec4(sphere_vertex_position + position, 1.0); 
}