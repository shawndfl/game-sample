#version 330 core

uniform vec4 u_color;
uniform mat4 u_projection;

layout (location = 0) in vec3 a_pos;						
layout (location = 1) in vec2 a_tex;

out vec2 v_tex;                          
                                              
void main() {                                
   gl_Position = u_projection  * vec4(a_pos, 1.0);  
   v_tex = a_tex;                            
}                                            
