#version 430 core
//Point Vert
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

varying vec4 colorV2F;
uniform mat4 viewProjection;

void main()
{
    colorV2F = color;
    gl_Position = viewProjection * vec4(position, 1.0);
}