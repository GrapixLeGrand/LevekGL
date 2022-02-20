#version 430

out vec4 out_color;
uniform vec4 color;

in vec3 normal;

void main()
{
    out_color = vec4(normal, 1.0);
}