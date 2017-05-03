#version 150

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;
//uniform mat4 normalMatrix;

uniform float displaceAmount;
in vec4 position;
in vec4 normal;

out vec4 vPosition;
out vec3 vNormal;

void main() {
    vNormal = normal.xyz;
    vec3 newPosition = position.xyz + vNormal * displaceAmount;
    //vPosition = modelViewProjectionMatrix * vec4( newPosition, 1.0 );
    gl_Position = vPosition;
    gl_Position = modelViewProjectionMatrix * position;
}
