#version 330 core

out vec4 FragColor;
in vec3 color;
in vec2 tex;

uniform sampler2D ourTexture;

void main() {
    vec4 color = texture(ourTexture, tex) * vec4(color, 1.0);    
	FragColor = color;
    //FragColor = vec4(ourColor,1.0);
}
