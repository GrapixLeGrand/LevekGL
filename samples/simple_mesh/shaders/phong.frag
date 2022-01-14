#version 430

out vec4 color;

in VERTEX_OUT {
    vec3 normalView;
    vec3 positionView;
    vec4 positionLightSpace;
} fragment_in;

uniform vec3 lightDirectionView;
uniform sampler2D shadowMap;
uniform float time_s;

vec4 ambiant = vec4(0.1, 0.2, 0.3, 1.0);
vec4 diffuse = ambiant;
vec4 specular = ambiant;
float shininess = 1.0;

//https://stackoverflow.com/questions/33360048/what-is-a-good-algo-for-glsl-lowp-random-number-generation-for-use-in-graphics
float rand(float frag_x, float frag_y, float t)
{
  float r = t*7.924;
  return 100.0*fract(sin(frag_y+frag_x)*r+sin(frag_y-frag_x)*r*.7);
}

// Gold Noise ©2015 dcerisano@standard3d.com
// - based on the Golden Ratio
// - uniform normalized distribution
// - fastest static noise generator function (also runs at low precision)
// - use with indicated seeding method. 

float PHI = 1.61803398874989484820459;  // Φ = Golden Ratio   

float gold_noise(in vec2 xy, in float seed){
       return fract(tan(distance(xy*PHI, xy)*seed)*xy.x);
}

//vec2 gold_noise_2D(in vec2 xy, in float seed, in float time) {
    //return vec2(fract(iTime)+1.0)
//}

void main() {

	vec3 lightDirection = -lightDirectionView;
    // diffuse shading
    float diff = max(dot(fragment_in.normalView, lightDirection), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDirection, fragment_in.normalView);
    float spec = pow(max(dot(-fragment_in.positionView, reflectDir), 0.0), shininess);

    //float c = 0.001;
    //shadow
    //project the position of fragment into normalized device space
    
    vec3 coordinatesNormalized = fragment_in.positionLightSpace.xyz / fragment_in.positionLightSpace.w;
    coordinatesNormalized = coordinatesNormalized * 0.5 + 0.5;
    
    float otherDepth = texture(shadowMap, coordinatesNormalized.xy).r;
    float thisDepth = coordinatesNormalized.z;
    //float shadow = otherDepth > (thisDepth - 0.0001) ? 1.0 : 0.0; //- 0.005

    vec2 rand_offset = vec2(0.0); //vec2(gold_noise(coordinatesNormalized.xy, fract(time_s * 1000.0)), gold_noise(coordinatesNormalized.xy, fract(time_s * 1000.0) + 1));

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, coordinatesNormalized.xy + (rand_offset + vec2(x, y)) * texelSize ).r; 
            shadow += thisDepth - 0.0001 < pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    //float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
	color = ambiant + shadow * ((diff * diffuse) + (specular * spec)); //vec4(1.0, 0.0, 0.0, 1.0);

}