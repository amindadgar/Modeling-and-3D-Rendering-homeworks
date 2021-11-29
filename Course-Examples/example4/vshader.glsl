#version 130
in vec4 vPosition;
out vec4 color;

void main(){
    color=vPosition;
    gl_Position = vPosition;
}
