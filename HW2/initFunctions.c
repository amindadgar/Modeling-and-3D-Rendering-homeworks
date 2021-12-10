#include <GL/glut.h>
#include "initFunctions.h"
#include "debuggingFunctions.h"
#include <stdio.h>

// define the border value of the window
#define BORDER 0.9

// this is the rate of ball moving
float BALL_ACTION = -1.0;

// the steps for changing ball position
float STEP_X = 0.01;
float STEP_Y = 0.01;

// default value is zero, DON'T CHANGE THIS VALUE!!!!
// if you want to enable debugging change this in the main.c function
int DEBUG = 0;


// the ball initializing position
float BALL_POSITION[15][2] = {
    {-0.03,0.03},
    {-0.04,0.015},
    {-0.045,0},
    {-0.04,-0.015},
    {-0.03,-0.03}, 
    {-0.015,-0.04}, 
    {0,-0.045},
    {0.015,-0.045},
    {0.03,-0.03},
    {0.04,-0.015},
    {0.045,0},
    {0.04,0.015},
    {0.03,0.03},
    {0.015,0.04},
    {0,0.04}
    }; 

 
// the first player position
float PLAYER_ONE_POSIOTION[4][2] = {
    {-0.8, -0.15},
    {-0.8,  0.15},
    {-0.75,  0.15},
    {-0.75, -0.15}
    }; 

// the second player position
float PLAYER_TWO_POSIOTION[4][2] = {
    {0.8, -0.15},
    {0.8,  0.15},
    {0.75,  0.15},
    {0.75, -0.15}
    }; 

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

    // Also reset the ball action
    BALL_ACTION = -1.0;

}

void reset_player_positions(){
    /*
        reset both player positions 
    */

   // reset first player
    PLAYER_ONE_POSIOTION[0][0] = -0.8;
    PLAYER_ONE_POSIOTION[0][1] = -0.15;

    PLAYER_ONE_POSIOTION[1][0] = -0.8;
    PLAYER_ONE_POSIOTION[1][1] = 0.15;

    PLAYER_ONE_POSIOTION[2][0] = -0.75;
    PLAYER_ONE_POSIOTION[2][1] = 0.15;

    PLAYER_ONE_POSIOTION[3][0] = -0.75;
    PLAYER_ONE_POSIOTION[3][1] = -0.15;

    // reset second player
    PLAYER_TWO_POSIOTION[0][0] = 0.8;
    PLAYER_TWO_POSIOTION[0][1] = -0.15;

    PLAYER_TWO_POSIOTION[1][0] = 0.8;
    PLAYER_TWO_POSIOTION[1][1] = 0.15;

    PLAYER_TWO_POSIOTION[2][0] = 0.75;
    PLAYER_TWO_POSIOTION[2][1] = 0.15;

    PLAYER_TWO_POSIOTION[3][0] = 0.75;
    PLAYER_TWO_POSIOTION[3][1] = -0.15;

}

void change_player_position(int player, int position){
    /*
        player == 1 is player_one
        player == 2 is player_two

        if position > 0 then move up
        else if position < 0 then move down
        */

    switch (player) {
        case 2:
            /* FIRST PLAYER */

            if (position > 0){

                // check the highest y value in player1 that doesn't go beyond the borders
                if (PLAYER_ONE_POSIOTION[1][1] + 0.05 < BORDER)
                {
                    // move all the y positions slightly up
                    PLAYER_ONE_POSIOTION[0][1] += 0.05;
                    PLAYER_ONE_POSIOTION[1][1] += 0.05;
                    PLAYER_ONE_POSIOTION[2][1] += 0.05;
                    PLAYER_ONE_POSIOTION[3][1] += 0.05;
                }

            } else if (position < 0){

                // check the lowest y value in player1 that doesn't go beyond the borders
                if(PLAYER_ONE_POSIOTION[0][1] - 0.05 > -1 * BORDER){
                    // move all the y positions slightly down
                    PLAYER_ONE_POSIOTION[0][1] -= 0.05;
                    PLAYER_ONE_POSIOTION[1][1] -= 0.05;
                    PLAYER_ONE_POSIOTION[2][1] -= 0.05;
                    PLAYER_ONE_POSIOTION[3][1] -= 0.05;
                }
            }
            break;


        case 1:
            /* SECOND PLAYER */

            // check the highest y value in player2 that doesn't go beyond the borders
            if(position > 0){
                if (PLAYER_TWO_POSIOTION[1][1] + 0.05 < BORDER){
                // move all the y positions slightly up
                    PLAYER_TWO_POSIOTION[0][1] += 0.05;
                    PLAYER_TWO_POSIOTION[1][1] += 0.05;
                    PLAYER_TWO_POSIOTION[2][1] += 0.05;
                    PLAYER_TWO_POSIOTION[3][1] += 0.05;
            }

            } else if (position < 0){

                // check the lowest y value in player2 that doesn't go beyond the borders
                if (PLAYER_TWO_POSIOTION[0][1] - 0.05 > -1 * BORDER ){
                        
                    // move all the y positions slightly down
                    PLAYER_TWO_POSIOTION[0][1] -= 0.05;
                    PLAYER_TWO_POSIOTION[1][1] -= 0.05;
                    PLAYER_TWO_POSIOTION[2][1] -= 0.05;
                    PLAYER_TWO_POSIOTION[3][1] -= 0.05;
                }

            }
            break;


        default:
            // print an error and close the program
            print_input_player_error(player);
            exit(1);
            break;
   }
}

void display_squares(){
    /*
        draw the squares for each player
    */

    // make the players color to red
    glColor3f(1,0,0);

    // first player
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i < 4;i++)
            glVertex2fv(PLAYER_ONE_POSIOTION[i]);
    glEnd();

    // second player
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i < 4;i++)
        glVertex2fv(PLAYER_TWO_POSIOTION[i]);
    glEnd();

    // make the color to defualt black
    glColor3f(0,0,0);

}


int change_ball_action( float player_y1, float player_y2,float player_x1, float player_x2,  float ball_x,float ball_y ){
    /*
        if the y of the ball was between the y of the player position ( Also ball x position was between player's x )
        else return the same ball action
    */

    if ( (player_y1 < ball_y && ball_y < player_y2) && (player_x1 <= ball_x && ball_x <= player_x2) ){

        // TODO: Changing steps here will corrupt the ball shape!!!!!! FIX THIS
        // change the way ball is going
        STEP_X = -1 * (player_y1 - ball_y) / 10;
        return BALL_ACTION * -1;

    } else 
        return BALL_ACTION;
}

void check_ball_hit_player(){
    /*
        check weather the ball hits a player or not
        if the ball didn't hit any player, return 0
        else return a number

        check the y of the ball that is between the y of the player's square
    */

   // 15 is the ball vertexes (array) length
   for (int i = 0; i < 15; i++){
       // to check the changes in action
       // if the action was changed, break the loop
       int ball_new_action = BALL_ACTION;

        // If the x of the ball was negative
        // then there's a chance for it to hit the first player 
        if( BALL_POSITION[i][0] < 0){
            // check the first player
            ball_new_action = change_ball_action(PLAYER_ONE_POSIOTION[0][1], PLAYER_ONE_POSIOTION[1][1],
             PLAYER_ONE_POSIOTION[0][0], PLAYER_ONE_POSIOTION[2][0],  BALL_POSITION[i][0], BALL_POSITION[i][1] );

            if( ball_new_action != BALL_ACTION){
                BALL_ACTION = ball_new_action;
                break;
            }
                
        } else {
            // check the second player
            ball_new_action = change_ball_action(PLAYER_TWO_POSIOTION[0][1], PLAYER_TWO_POSIOTION[1][1],
                 PLAYER_TWO_POSIOTION[2][0], PLAYER_TWO_POSIOTION[0][0] , BALL_POSITION[i][0], BALL_POSITION[i][1]);

            if( ball_new_action != BALL_ACTION ){
                BALL_ACTION = ball_new_action;
                break;
            }
        }
   }
} 

void change_ball_position(int index){
    /*
        change the ball in the way it is going
        index is the index of the ball

        BALL_ACTION  is the rate of how the ball position increasing or decreasing
    */
        
    // increase ball position each time it is shown
    BALL_POSITION[index][0] += STEP_X * BALL_ACTION;
    BALL_POSITION[index][1] += STEP_Y * BALL_ACTION;

    // if it reach the borders
    if (BALL_POSITION[index][0] >= BORDER || BALL_POSITION[index][0] <= -1* BORDER){
        reset_ball_positions();

        reset_ball(DEBUG);
    } else if(BALL_POSITION[index][1] >= BORDER || BALL_POSITION[index][1] <= -1* BORDER){
        // BALL_ACTION = BALL_ACTION * -1;

        // TODO: Changing steps here will corrupt the ball shape!!!!!! FIX THIS
        STEP_Y = STEP_Y * -1;
        STEP_X = STEP_X * -1;
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
    
    // check if the ball that hits the player or not
    check_ball_hit_player();

   glColor3f(0, 0.0, 0.0);

}

void display_game_window(){
    /*
        There is a square that the game is happening within it
    */
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-1 * BORDER, -1 * BORDER);
        glVertex2f(-1 * BORDER, BORDER);
        glVertex2f(BORDER, BORDER);
        glVertex2f(BORDER, -1 * BORDER);
    glEnd();

}