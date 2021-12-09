#include <GL/glut.h>
#include <stdio.h>
#include "initFunctions.h"


#define MAX_WINDOW_WIDTH 640
#define MAX_WINDOW_HEGHT 480


// to enable debugging assign any number rather than zero to this in the main function
extern int DEBUG;


void display_objects(int info);
void init_display();

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(MAX_WINDOW_WIDTH, MAX_WINDOW_HEGHT);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Ping Pong");

    /* if you want to enable debugging uncomment the code below */
    // DEBUG = 1;
    
    init_display();

    glutMainLoop();

}

void init_display(){
    /*
        initialize the display
        remove colors and make a white background
        
    */

   // set background to white
   // and remove the color buffer
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    

    // Run the game using glutTimer callback function
    glutTimerFunc(20, display_objects, 0);

}

void display_objects(int info){

    /*
        display the objects with their moving position
    */
    glClear(GL_COLOR_BUFFER_BIT);

    display_game_window();
    display_squares();
    display_ball();
    display_game_window();

    glFlush();
    glutTimerFunc(20, display_objects, 0);

}