#version 430

//a tutorial https://paroj.github.io/gltut/Illumination/Tutorial%2013.html
out vec4 out_color;

in VERTEX_OUT {
    vec3 normalView;
    vec3 positionView;
    vec2 uv;
} fragment_in;

uniform vec4 palette[1024];
flat in uint palette_index_v2f;

void main()
{   
    //float diff = max(dot(fragment_in.normalView, -normalize(vec3(-0.5, -0.5, -0.5))), 0.0);
    vec4 color = palette[palette_index_v2f];
    out_color = color; // * 0.5 + 0.5 * color * diff;
}