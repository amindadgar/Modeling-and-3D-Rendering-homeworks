# Modeling-and-3D-Rendering-homeworks
This repository contains the codes for my Modeling and 3D Rendering university course. In the course we're learning graphic programming using OpenGL API.<br>
## Homwork #1
**Question:** Create a program that draw triangle with 3 mouse clicks coordinates. <br>
**Answer:** [HW1/HW1.c](https://github.com/amindadgar/3D-modeling-and-rendering-homeworks/blob/main/HW1/HW1.c)

### To Run the project
First of all make sure you've installed g++ compiler and glut library. <br>
Then to run the project simply use this command: 
```
g++ HW1.c -o hw1.out -lGL -lGLU -lglut
```

### Notes
The program was made and tested on Ubuntu 20.04 LTS System

## Homework #2
**Question:** Please write a C code to implement a Ping-Pong game with OpenGL which works as follows:
1. Define a small circle as a ball in a rectangular area.
2. With a first mouse click (left button), the ball start moving toward the position clicked.
3. When the ball reach border of the rectangle it is bounced just like when light hit a mirror.
4. Define two small rectangles in areas close to the right and left sides which works like a tennis
rocket when the ball hit them.
5. The rocket moves up or down to the sides of rectangle by pressing some keys.
6. Each player should prevent the ball hitting its side of the rectangle.
7. If the ball hit the side behind the rocket the opposite player gets one score.
8. A pop-up menu is opened with a right mouse click with 3 entries of "Exit", "Start over" and
"Level". "Level" opens a sub menu with three entries of "Easy", "Medium" and "Hard".
9. The initial speed of ball, is adjusted based on the level selected.
10. The current scores of two players should be displayed somewhere on the display.

**Answer:** [Homework 2 Codes](https://github.com/amindadgar/3D-modeling-and-rendering-homeworks/tree/main/HW2)

### To Run the project
Use The command:
```
g++ main.c initFunctions.c debuggingFunctions.c -o main.out -lGL -lGLU -lglut
```
Then To Run:
```
./main.out
```
## Homework #3
**Question:** Create a shader base format of Homework number 2. <br>
**Answer:** [Homework 3 Codes](https://github.com/amindadgar/3D-modeling-and-rendering-homeworks/blob/07c2fca854da4ecfaa6f17c0ef3d9bfcce638886/HW3)

### To Run the project
Use The command:
```
g++ main.c initFunctions.c debuggingFunctions.c -o main.out -lGL -lGLU -lglut -lGLEW
```
Then To Run:
```
./main.out
```

### Notes
The program was made and tested on Ubuntu 20.04 LTS System

## Course-Examples
This directory contains the examples recieved from Professor of this course.

## Course Reference
The course reference is the book: Edward Angel, Dave Shreiner - Interactive Computer Graphics_ A Top-Down Approach with Shader-Based OpenGL, 6th Edition  -Addison Wesley (2011).
