#version 430

out vec4 out_color;

in VERTEX_OUT {
    vec4 positionLightSpace;
    vec2 uv;
} fragment_in;

uniform sampler2D tex;
uniform sampler2D shadowMap;

#define RADIUS 2
#define TOTAL (2 * RADIUS) + 1

#define TOTAL_2 (TOTAL) * (TOTAL)

void main()
{   
    vec3 coordinatesNormalized = fragment_in.positionLightSpace.xyz / fragment_in.positionLightSpace.w;
    coordinatesNormalized = coordinatesNormalized * 0.5 + 0.5;
    //float otherDepth = texture(shadowMap, coordinatesNormalized.xy).r;
    float thisDepth = coordinatesNormalized.z;

    float factor = 0.0; //otherDepth > thisDepth ? 1.0 : 0.5;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -RADIUS; x <= RADIUS; ++x) {
        for(int y = -RADIUS; y <= RADIUS; ++y) {
            float pcfDepth = texture(shadowMap, coordinatesNormalized.xy + vec2(x, y) * texelSize).r; 
            factor += thisDepth < pcfDepth ? 1.0 : 0.0;        
        }
    }
    factor /= TOTAL_2;
    factor *= 0.5;
    factor += 0.5;
    
    out_color = texture(tex, fragment_in.uv);
    out_color.rgb *= factor;
}