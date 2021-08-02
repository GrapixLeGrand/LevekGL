#version 430 core
//Point Frag
out vec4 FragColor;

varying vec4 colorV2F;

void main()
{
    FragColor = colorV2F;
}