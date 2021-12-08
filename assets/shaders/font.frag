#version 330 core
                 
in vec2 v_tex;                      
uniform sampler2D u_font;                             
uniform vec4 u_color;
out vec4 color;
                    
void main() {                            
    vec2 tex = v_tex;
    color = texture2D(u_font, tex) * u_color; 
}                                         
                                                 