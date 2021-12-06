#include <GL/glut.h>
#include "initFunctions.h"

void init_squares(){
    /*
        draw the squares for each player
    */

   // make the players color to red
   glColor3f(1,0,0);

   // first player
   glBegin(GL_TRIANGLE_FAN);
        glVertex2f(-0.8, -0.15);
        glVertex2f(-0.8,  0.15);
        glVertex2f(-0.75,  0.15);
        glVertex2f(-0.75, -0.15);
    glEnd();

    // second player
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.8, -0.15);
        glVertex2f(0.8,  0.15);
        glVertex2f(0.75,  0.15);
        glVertex2f(0.75, -0.15);
    glEnd();

    // make the color to defualt black
    glColor3f(0,0,0);

}

void init_ball(){
    /*
        initialize the ball at the middle of the window
    */
   glColor3f(0.5, 0.5, 0.5);
   glBegin(GL_POLYGON);
        glVertex2f(-0.03,0.03);
        glVertex2f(-0.04,0.015);
        glVertex2f(-0.05,0);
        glVertex2f(-0.04,-0.015);
        glVertex2f(-0.03,-0.03);
        glVertex2f(-0.015,-0.04);
        glVertex2f(0,-0.05);
        glVertex2f(0.015,-0.045);
        glVertex2f(0.03,-0.03);
        glVertex2f(0.04,-0.015);
        glVertex2f(0.05,0);
        glVertex2f(0.04,0.015);
        glVertex2f(0.03,0.03);
        glVertex2f(0.015,0.045);
        glVertex2f(0,0.05);

   glEnd();

   glColor3f(0, 0.0, 0.0);


}

void init_game_window(){
    /*
        There is a square that the game is happening within it
    */
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.9, -0.9);
        glVertex2f(-0.9, 0.9);
        glVertex2f(0.9, 0.9);
        glVertex2f(0.9, -0.9);
    glEnd();

}