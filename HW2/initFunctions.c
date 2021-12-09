#include <GL/glut.h>
#include "initFunctions.h"
#include "debuggingFunctions.h"

// define the border value of the window
#define BOARDER 0.9

// default value is zero, DON'T CHANGE THIS VALUE!!!!
// if you want to enable debugging change this in the main.c function
int DEBUG = 0;

float BALL_POSITION[15][2] = {
    {-0.03,0.03}, //0
    {-0.04,0.015}, //1
    {-0.045,0}, // 2
    {-0.04,-0.015}, //3
    {-0.03,-0.03}, //4 
    {-0.015,-0.04}, //5 
    {0,-0.045}, //6
    {0.015,-0.045}, //7
    {0.03,-0.03}, //8
    {0.04,-0.015}, //9
    {0.045,0},  //10
    {0.04,0.015}, //11
    {0.03,0.03}, // 12
    {0.015,0.04},  //13
    {0,0.04}};  //14


void reset_ball_positions(){
    /*
        if ball hits the border reset it
    */
    BALL_POSITION[0][0] = -0.03;
    BALL_POSITION[0][1] = 0.03;

    BALL_POSITION[1][0] = -0.04;
    BALL_POSITION[1][1] = 0.015;

    BALL_POSITION[2][0] = -0.045;
    BALL_POSITION[2][1] = 0;

    BALL_POSITION[3][0] = -0.04;
    BALL_POSITION[3][1] = -0.015;

    BALL_POSITION[4][0] = -0.03;
    BALL_POSITION[4][1] = -0.03;

    BALL_POSITION[5][0] = -0.015;
    BALL_POSITION[5][1] = -0.04;

    BALL_POSITION[6][0] = 0;
    BALL_POSITION[6][1] = -0.045;

    BALL_POSITION[7][0] = 0.015;
    BALL_POSITION[7][1] = -0.045;

    BALL_POSITION[8][0] = 0.03;
    BALL_POSITION[8][1] = -0.03;

    BALL_POSITION[9][0] = 0.04;
    BALL_POSITION[9][1] = -0.015;

    BALL_POSITION[10][0] = 0.045;
    BALL_POSITION[10][1] = 0;

    BALL_POSITION[11][0] = 0.04;
    BALL_POSITION[11][1] = 0.015;

    BALL_POSITION[12][0] = 0.03;
    BALL_POSITION[12][1] = 0.03;

    BALL_POSITION[13][0] = 0.015;
    BALL_POSITION[13][1] = 0.04;

    BALL_POSITION[14][0] = 0;
    BALL_POSITION[14][1] = 0.04;

}
void display_squares(){
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

void change_ball_position(int index){
    /*
        change the ball in the way it is going
    */

        // increase ball position each time it is shown
        BALL_POSITION[index][0] += 0.01;
        BALL_POSITION[index][1] += 0.01;

        // if it reach the borders
        if (BALL_POSITION[index][0] > BOARDER){
            reset_ball_positions();

            reset_ball(DEBUG);
        }

}

void display_ball(){
    /*
        display the ball and move its position
    */
   glColor3f(0.5, 0.5, 0.5);
   glBegin(GL_POLYGON);

    for(int i = 0; i < 15;i++){

        glVertex2f(BALL_POSITION[i][0],
            BALL_POSITION[i][1]);

        print_ball_positions(BALL_POSITION[i][0], BALL_POSITION[i][1], i, DEBUG);

        // change the ball in the way it is going
        change_ball_position(i);

    }
   glEnd();

   glColor3f(0, 0.0, 0.0);

}

void display_game_window(){
    /*
        There is a square that the game is happening within it
    */
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1 * BOARDER, -1 * BOARDER);
        glVertex2f(-1 * BOARDER, BOARDER);
        glVertex2f(BOARDER, BOARDER);
        glVertex2f(BOARDER, -1 * BOARDER);
    glEnd();

}