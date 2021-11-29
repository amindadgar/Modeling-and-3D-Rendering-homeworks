#version 130
in vec4 color;

void main(){
    gl_FragColor=vec4((1.0 + color.xyz)/2.0,1.0);
}
