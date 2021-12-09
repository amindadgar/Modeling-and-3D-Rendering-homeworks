#include "debuggingFunctions.h"
#include <stdio.h>


#define GREEN_MESSAGE   "\033[32m"      // GREEN Color for printf
#define RESET_MESSAGE_COLOR   "\033[0m"       // Reset Coloring for printf

void print_ball_positions(float posx, float posy, int index, int debug_mode){
    /*
        To print ball positions
        posx and posy are position x and y for the ball in the window
        debug_mode is an integer contains to print debugs or not!
        index is the BALL_POSITION array index ( array in initFunctions.c )
        the BALL_POSITION array size is 14
    */
   if (debug_mode){
        printf("New Ball vertex %d/14 Position: [%f,%f]\n", index, posx, posy);
   }
   
}

void reset_ball(int debug_mode){
    /*
        reset ball position message
        if debug_mode was a number other than zero, it will print the message
    */
    if (debug_mode)
    {
        printf(GREEN_MESSAGE "BALL position resets to center!\n" RESET_MESSAGE_COLOR);
    }
    
}

