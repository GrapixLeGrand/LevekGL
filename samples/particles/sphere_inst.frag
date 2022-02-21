#version 430

out vec4 out_color;
uniform vec4 color;

in vec3 v2f_normal;
in vec2 v2f_uv;

void main()
{   
    /*
    float dist = (0.5 - v2f_uv.x) * (0.5 - v2f_uv.x) + (0.5 - v2f_uv.y) * (0.5 - v2f_uv.y);
    if (dist < 0.5) {
        out_color = vec4(v2f_normal, 1.0);
    } else {
        out_color = vec4(0.0);
    }*/
    out_color = vec4(v2f_normal, 1.0);
}