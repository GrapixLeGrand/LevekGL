#version 430

out vec4 out_color;

uniform mat4 p;
uniform mat4 v;
uniform vec3 light_direction;

in vec3 v2f_normal;
in vec2 v2f_uv;
in vec3 v2f_position_view;


vec3 ambiant = vec3(0.8, 0.1, 0.2);
vec3 white = vec3(1.0);
float shininess = 1.0;


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
        
        vec3 light_dir = (v * vec4(light_direction, 1.0)).xyz;
        float diff = max(dot(normal, light_dir), 0.0);
        vec3 reflect_dir = reflect(-light_dir, normal);
        float spec = pow(max(dot(-position, reflect_dir), 0.0), shininess);

        out_color = vec4(ambiant + diff * ambiant + spec * ambiant, 1.0);
    } else {
        discard;
    }

    
}