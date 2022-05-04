#version 330 core

in vec3 normal;
in vec2 tex;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform float ambientStrength;
uniform sampler2D ourTexture;

void main() {
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    vec4 diffusedTex = texture(ourTexture, tex);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffused = diff * lightColor * diffusedTex.rgb;
    
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 result = ambient + diffused; 
        
	  FragColor = vec4(result, diffusedTex.a);    
}
