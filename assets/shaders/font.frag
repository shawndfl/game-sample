#version 330 core
                 
in vec2 v_tex;                      
uniform sampler2D u_font;                             
uniform vec4 u_color;
out vec4 color;
                    
void main() {                                
    color = texture(u_font, v_tex);// * u_color;
    if(color.r <= 0.01) {
        discard;
    }
}                                         
                                                 
