#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNormal;

out vec3 normal;
out vec2 tex;
out vec3 fragPos;

uniform float ambientStrength;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform mat4 model;
uniform mat4 normalMat;
uniform mat4 view;
uniform mat4 proj;

void main() { 
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    vec4 vertPos4 = model * vec4(aPos, 1.0);    
    fragPos = vertPos4.xyz / vertPos4.w;
    tex = aTex;
    normal = vec3(normalMat * vec4(aNormal, 0.0));
    
 }