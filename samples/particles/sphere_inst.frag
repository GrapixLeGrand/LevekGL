#version 430

//a tutorial https://paroj.github.io/gltut/Illumination/Tutorial%2013.html
out vec4 out_color;

uniform mat4 p;
uniform mat4 v;
uniform vec3 light_direction;
uniform mat3 view_inv;

uniform mat3 normal_view;
uniform mat3 normal_view_inv;
uniform mat4 view_inv_t;

in vec3 v2f_normal;
in vec2 v2f_uv;
in vec3 v2f_position_view;
in vec3 v2f_position;

vec3 ambiant = vec3(0.8, 0.1, 0.2);
vec3 white = vec3(1.0);
float shininess = 1.0;

in vec3 v0;
in vec3 v1;

float radius = 0.5;

void main()
{   

    vec2 uv = 2.0 * (v2f_uv - vec2(0.5, 0.5));
    float len = dot(uv, uv);

    if (len <= 1.0) {
        
        //uv.y *= -1;
        vec3 normal = vec3(uv, sqrt(1.0 - len)); //in camera position
        vec3 position = normalize(normal) * radius + v2f_position_view;
        vec4 clipPos = p * vec4(position, 1.0);
        float depth_ndc = clipPos.z / clipPos.w; 
        gl_FragDepth = ((gl_DepthRange.diff * depth_ndc) + gl_DepthRange.near + gl_DepthRange.far) / 2.0;
        //light_direction;


        //vec4 light_dir4 = light_direction; //v * vec4(light_direction, 1.0); //(v * vec4(light_direction, 1.0)).xyz;
        vec3 light_dir = light_direction;//- normalize(normal_view * light_direction); //normal_view * light_direction; //light_dir4.xyz / light_dir4.w
        
        mat3 temp = transpose(view_inv);

        float diff = max(dot(normal, light_dir), 0.0);
        vec3 reflect_dir = reflect(-light_dir, normal);
        float spec = pow(max(dot(-position, reflect_dir), 0.0), shininess);
        
        /*
        //out_color = vec4(ambiant + diff * ambiant, 1.0);
        vec3 world_pos_frag = (view_inv_t * vec4(position, 1.0)).xyz;
        vec3 world_normal = world_pos_frag - v2f_position;
        vec3 world_pos_normal = (view_inv_t * vec4(normal, 1.0)).xyz;

        diff = max(dot(normalize(world_pos_normal), light_dir), 0.0);
        //vec4(normalize(world_normal), 1.0); //*/ //vec4(normalize(temp * normal), 1.0);
        /*
        vec3 world_pos_frag = inverse(view_inv) * position - v2f_position;

        vec3 v2 = cross(v0, v1);

        vec4 v00 = vec4(v0, 0.0);
        vec4 v11 = vec4(v1, 0.0);
        vec4 v22 = vec4(v2, 0.0);
        vec4 v33 = vec4(v2f_position, 1.0);

        mat4 world_to_bb = mat4(v00, v11, v22, v33);
        mat3 bb_to_world = mat3(inverse(transpose(world_to_bb)));
        */
        out_color = vec4(ambiant + diff * ambiant, 1.0); // vec4(normalize(bb_to_world * normal), 1.0);//vec4(normalize(temp * ( normal)), 1.0); 
    } else {
        discard;
    }

    
}