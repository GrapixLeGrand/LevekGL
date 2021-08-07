#version 430 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec2 l_texture;

out vec2 v2f_texture;

void main() {
    v2f_texture = l_texture;
    gl_Position = vec4(l_position.x, l_position.y, l_position.z, 1.0);   
}