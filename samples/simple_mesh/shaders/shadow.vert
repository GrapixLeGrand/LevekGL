#version 430 core
//Depth vert
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

uniform mat4 light_mvp;

void main()
{
    gl_Position = light_mvp * vec4(position, 1.0);
}  