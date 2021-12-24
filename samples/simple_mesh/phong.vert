#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

out VERTEX_OUT {
    vec3 normalView;
    vec3 positionView;
    vec4 positionLightSpace;
} vertex_out;

//varying vec3 normalViewV2F;
//varying vec3 positionViewV2F;

uniform mat4 mvp;
uniform mat4 mv;
uniform mat3 normalMatrix;

//shadow
uniform mat4 light_mvp;

void main() {
    vertex_out.normalView = normalize(normalMatrix * normal);
    vertex_out.positionView = normalize((mv * vec4(position, 1)).xyz); //cam pos in cam basis = (0,0,0) => posCam - (0,0,0)
    vertex_out.positionLightSpace = light_mvp * vec4(position, 1);
    gl_Position = mvp * vec4(position, 1.0);
}