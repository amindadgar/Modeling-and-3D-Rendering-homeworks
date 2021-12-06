#include <GL/glut.h>
#include <stdio.h>
#include "initFunctions.h"



int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Ping Pong");

    init_display();
    init_squares();
    init_ball();
    init_game_window();

    glFlush();
    glutMainLoop();

}

void init_display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    
}

void display_callbackFunc(){

}