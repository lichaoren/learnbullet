#version 330 core

// inputs:
// all interpolated by the vertex shader
in vec2 UV;
in vec3 vertexPos_w;
in vec3 vertexNor_c;
in vec3 eyeDir_c;
in vec3 lightDir_c; 


// output color
out vec3 color;

// values that stay constant for the whole mesh
uniform sampler2D txSampler;
uniform mat4 MV;
uniform vec3 lightPos_w;

void main() {
    // light properties
    vec3 lightColor = vec3(1, 1, 1);
    float lightPower = 30.0f;
    
    // material properties
    vec3 diffColor = texture2D( txSampler, UV ).rgb;
    vec3 ambColor = vec3( 0.1, 0.1, 0.1 ) * diffColor;
    vec3 specColor = vec3( 0.6, 0.6, 0.6 );
    
    // distant to lights
    float distance = length( lightPos_w - vertexPos_w );
    
    // normal of current point
    vec3 n = normalize( vertexNor_c );
    // direction of light
    vec3 l = normalize( lightDir_c );
    
    float cosTheta = clamp( dot(n, l), 0, 1 );
    
    // eye vector towards the camera
    vec3 E = normalize( eyeDir_c );
    // reflected light direction
    vec3 R = reflect( -l, n );
    
    float cosAlpha = clamp( dot(E, R), 0, 1);

    // output color compute here
    color = ambColor +
            diffColor * lightColor * lightPower * cosTheta / ( distance * distance ) +
            specColor * lightColor * lightPower * pow(cosAlpha, 5) / (distance * distance);
}