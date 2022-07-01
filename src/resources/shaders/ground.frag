#version 430

out vec4 out_color;

in VERTEX_OUT {
    vec4 positionLightSpace;
    vec2 uv;
} fragment_in;

uniform sampler2D tex;
uniform sampler2D shadowMap;

void main()
{   
    vec3 coordinatesNormalized = fragment_in.positionLightSpace.xyz / fragment_in.positionLightSpace.w;
    coordinatesNormalized = coordinatesNormalized * 0.5 + 0.5;
    float otherDepth = texture(shadowMap, coordinatesNormalized.xy).r;
    float thisDepth = coordinatesNormalized.z;

    float factor = otherDepth > thisDepth ? 1.0 : 0.5;

    /*
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, coordinatesNormalized.xy + vec2(x, y) * texelSize).r; 
            shadow += thisDepth - 0.0001 < pcfDepth ? 1.0 : 0.0;        
        }
    }
    shadow /= 9.0;
    */
    vec2 c = fragment_in.uv;
    out_color = texture(tex, 30.0 * c);
    out_color.rgb *= factor;
}