#version 430

out vec4 out_color;

uniform mat4 p;


in vec3 v2f_normal;
in vec2 v2f_uv;
in vec3 v2f_position_view;

float radius = 0.5;

void main()
{   

    vec2 uv = 2.0 * (v2f_uv - vec2(0.5, 0.5));
    float len = dot(uv, uv);

    if (len <= 1.0) {
        vec3 normal = vec3(uv, sqrt(1.0 - len));
        vec3 position = normal * radius + v2f_position_view;
        vec4 clipPos = p * vec4(position, 1.0);
        float depth_ndc = clipPos.z / clipPos.w; 
        gl_FragDepth = ((gl_DepthRange.diff * depth_ndc) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
        out_color = vec4(normal, 1.0);
    } else {
        discard;
    }

    
}