#version 150

in vec4 v_position;
out vec4 vcolor;

void main(){
    gl_Position = v_position;
    
    // create custom colors depend on the position
    vcolor = vec4((v_position.x + 1) / 2, (v_position.y + 1) / 2, 0, 1.0);
}