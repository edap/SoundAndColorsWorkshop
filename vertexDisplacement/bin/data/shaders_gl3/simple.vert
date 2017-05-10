#version 150

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;

uniform float displaceAmount;
in vec4 position;
in vec4 normal;

out vec4 vPosition;
out vec3 vNormal;

void main() {
    vNormal = normal.xyz;
    vPosition = position;
    vec3 newPosition = position.xyz + vNormal * displaceAmount;
    gl_Position = modelViewProjectionMatrix * vec4( newPosition, 1.0 );
}
