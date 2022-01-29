#version 430 core

layout (location = 0) in vec3 sphere_vertex_position;
layout (location = 1) in vec2 sphere_vertex_uv;
layout (location = 2) in vec3 sphere_vertex_normal;
layout (location = 3) in vec3 position;

out vec4 out_color;
uniform vec4 color;

void main()
{
    out_color = vec4(sphere_vertex_normal, 1.0);
}