#version 150
uniform vec3 lightPos;
uniform vec4 materialColor;

in vec4 vPosition;
in vec3 vNormal;

out vec4 vFragColor;

void main() {
    vec4 color = vec4(materialColor);
    // light position and vertex position have always to be
    // in the same space coordinatas.
    vec3 lightDirection = normalize(lightPos - vPosition.xyz);
    float dProd = max(0.3, dot(vNormal, lightDirection));
    vec4 colorWithLight = vec4( vec3( dProd ) * vec3( color ), 1.0 );
    vFragColor = colorWithLight;
}
