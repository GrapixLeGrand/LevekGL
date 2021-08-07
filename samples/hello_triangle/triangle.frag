#version 430 core

out vec4 FragColor;

in vec2 v2f_texture;

uniform float u_time; 

void main() {

    float r = mod(v2f_texture.x + u_time, 1.0);
    float g = mod(v2f_texture.y + u_time, 1.0);
    float b = mod(v2f_texture.x + v2f_texture.y + u_time, 1.0);

    FragColor = vec4(r, g, b, 1.0);
}