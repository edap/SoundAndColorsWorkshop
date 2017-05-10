#version 150

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
uniform mat4 normalMatrix;

uniform float displaceAmount;
in vec4 position;
in vec4 normal;

out vec4 vPosition;
out vec3 vNormal;

void main() {
    vNormal = normal.xyz;
    // VPosition it is used for the light calculation
    vPosition = position;
    gl_Position = modelViewProjectionMatrix * position;
}
