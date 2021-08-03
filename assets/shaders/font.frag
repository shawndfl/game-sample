#version 330 core
                 
varying vec2 v_tex;
                      
uniform sampler2D u_font;
            
uniform vec2 u_scale;                    
uniform vec2 u_offset;                   
uniform vec4 u_color;
                    
void main() {                            
    vec2 tex = u_offset + v_tex * u_scale;
    gl_FragColor = texture2D(u_diffused, tex) * u_color; 
}                                         
                                                 