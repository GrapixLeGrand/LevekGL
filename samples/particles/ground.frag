#version 430

out vec4 out_color;

in vec2 v2f_tex_coord;
uniform sampler2D tex;

void main()
{
    out_color = texture(tex, v2f_tex_coord); //vec4(v2f_tex_coord, 0.0, 1.0);
}