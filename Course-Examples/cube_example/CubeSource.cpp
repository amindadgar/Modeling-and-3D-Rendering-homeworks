#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib,"glew32.lib")
#define NoP 36

class points
{
public:
	GLfloat	x,y,z,w;
	points()
	{
		x=y=z=0;
		w=1;
	}
	points(GLfloat ix, GLfloat iy, GLfloat iz, GLfloat iw)
	{
		x=ix; y=iy; z=iz; w=iw;
	}
	points(GLfloat ix, GLfloat iy, GLfloat iz)
	{
		x=ix; y=iy; z=iz; w=1;
	}

};
class Vcolors
{
public:
	GLfloat r, g, b, a;
	Vcolors()
	{
		r=g=b=0; a=1;
	}
	Vcolors(GLfloat ir, GLfloat ig, GLfloat ib, GLfloat ia)
	{
		r=ir; g=ig; b=ib; a=ia;
	}
	Vcolors(GLfloat ir, GLfloat ig, GLfloat ib)
	{
		r=ir; g=ig; b=ib;
	}
};

void idle();
void mouse(int,int,int,int);
void keyboard(unsigned char, int, int);
void mydisplay();
void Creat2Triangle(int, int, int, int);
void colorcube();
void init();
void CubePoints(points [], Vcolors []);
GLuint InitShader(char *, char *);

points Tpoints[NoP];
Vcolors Tcolors[NoP];
int Index=0;
points	vertex_positions[8];
Vcolors	vertex_colors[8];
enum { Xaxis =0, Yaxis=1,Zaxis=2,NumAxes=3};
int Axis =Xaxis;
float step = 0.1;
GLuint thetaHandle;  // theta uniform location
   // Axis angles
GLfloat Theta[3]={10.0,10.0,10.0};//determins the rotation aroun x, y and z axes

int main(int argc, char** argv)
{

	glutInit(&argc,  argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Rotating Color Cube");
	glewInit();
	init();
	glutDisplayFunc(mydisplay);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

void init()
{
	GLuint buffer;
	CubePoints(vertex_positions, vertex_colors);
	
	GLuint program;
	program = InitShader("vshader.glsl","fshader.glsl");
	glUseProgram(program);
	
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Tpoints) + sizeof(Tcolors),
		NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0,sizeof(Tpoints), Tpoints );
	glBufferSubData( GL_ARRAY_BUFFER, sizeof(Tpoints),
		sizeof(Tcolors), Tcolors );

	GLuint loc = glGetAttribLocation(program, "points");
	glEnableVertexAttribArray ( loc );
	glVertexAttribPointer( loc, 4, GL_FLOAT, GL_FALSE,0, 0);//BUFFER_OFFSET(0));
	GLuint vc = glGetAttribLocation( program, "Vcolors" );
	glEnableVertexAttribArray( vc );
	glVertexAttribPointer( vc, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid *) sizeof(Tpoints) );
	
	thetaHandle = glGetUniformLocation( program, "theta" );
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}
void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //the clear call will affect the color buffer
	glUniform3fv( thetaHandle, 1, Theta );
	glDrawArrays(GL_TRIANGLES,0,NoP);  //Rendering
	glutSwapBuffers();  //Swap front and back buffers
}

static char * ReadShaderSource(char * ShaderFile)
{
	FILE *fp;
	fp = fopen(ShaderFile,"rt");
	if (!fp) return NULL;
	long size=0;
	while (!feof(fp))
	{
      fgetc (fp);
      size++;
    }
	size--;
	fseek(fp, 0, SEEK_SET);
	char * buf= new char[size + 1];
	fread(buf, 1, size,fp);
	buf[size]=0;
	fclose(fp);
	return buf;
}
GLuint InitShader(char * vShaderFile, char * fShaderFile)
{
	char * svs, * sfs; 
	GLuint program, VertexShader, FragmentShader;

	program = glCreateProgram();
	VertexShader = 	glCreateShader(GL_VERTEX_SHADER);
	svs=ReadShaderSource(vShaderFile);
	printf("\n %s",svs);
	glShaderSource(VertexShader,1,(const GLchar **)&svs,NULL);
	glCompileShader(VertexShader);
	
	
	GLint compiled;
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{	printf("/n failed to compile");
		GLint logSize;
		glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH,&logSize);
		char * logMsg = new char[logSize];
		glGetShaderInfoLog(VertexShader, logSize, NULL, logMsg);
		printf("\n  %s",logMsg);
		getchar();
		delete [] logMsg;
		exit(EXIT_FAILURE);
	}
	
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	sfs = ReadShaderSource(fShaderFile);
	printf("\n  %s",sfs);
	glShaderSource(FragmentShader, 1, (const GLchar **)&sfs, NULL);
	glCompileShader(FragmentShader);
	
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &compiled);
	if(!compiled)
	{	printf("\n failed to compile");
		GLint logSize2;
		glGetShaderiv(FragmentShader, GL_INFO_LOG_LENGTH,&logSize2);
		char logMsg2[161];// = new char[162];//logSize2];
		glGetShaderInfoLog(FragmentShader, logSize2, NULL, logMsg2);
		printf("\n  %s",logMsg2);
		getchar();
		delete [] logMsg2;
		exit(EXIT_FAILURE);
	}
	glAttachShader(program, VertexShader);
	glAttachShader(program, FragmentShader);
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(!linked)
	{	printf("/n failed to link");
		GLint logSize;
		glGetShaderiv(VertexShader, GL_INFO_LOG_LENGTH,&logSize);
		char * logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		printf("\n  %s",logMsg);
		delete [] logMsg;
		exit(EXIT_FAILURE);
	}

	return program;
}
void CubePoints(points vertex_positions[], Vcolors vertex_colors[])
{
	
	vertex_positions[0] = points(-0.5, -0.5,  0.5, 1.0);
	vertex_positions[1] = points(-0.5,  0.5,  0.5, 1.0);
	vertex_positions[2] = points( 0.5,  0.5,  0.5, 1.0);
	vertex_positions[3] = points( 0.5, -0.5,  0.5, 1.0);
	vertex_positions[4] = points(-0.5, -0.5, -0.5, 1.0);
	vertex_positions[5] = points(-0.5,  0.5, -0.5, 1.0);
	vertex_positions[6] = points( 0.5,  0.5, -0.5, 1.0);
	vertex_positions[7] = points( 0.5, -0.5, -0.5, 1.0);
		
	vertex_colors[0] = Vcolors(0.0, 0.0, 1.0, 1.0);  // blue
	vertex_colors[1] = Vcolors(0.0, 1.0, 1.0, 1.0);  // cyan
	vertex_colors[2] = Vcolors(1.0, 1.0, 1.0, 1.0);  // white
	vertex_colors[3] = Vcolors(1.0, 0.0, 1.0, 1.0);  // magenta		
	vertex_colors[4] = Vcolors(0.0, 0.0, 0.0, 1.0);	 // black
	vertex_colors[5] = Vcolors(0.0, 1.0, 0.0, 1.0);  // green
	vertex_colors[6] = Vcolors(1.0, 1.0, 0.0, 1.0);  // yellow
	vertex_colors[7] = Vcolors(1.0, 0.0, 0.0, 1.0);  // red
	colorcube();
}
void colorcube()
{
    Creat2Triangle( 1, 0, 3, 2 );
    Creat2Triangle( 2, 3, 7, 6 );
    Creat2Triangle( 3, 0, 4, 7 );
    Creat2Triangle( 6, 5, 1, 2 );
    Creat2Triangle( 4, 5, 6, 7 );
    Creat2Triangle( 5, 4, 0, 1 );
}
void Creat2Triangle(int a, int b, int c, int d)
{
	Tcolors[Index] = vertex_colors[a]; Tpoints[Index] = vertex_positions[a]; Index++;
    Tcolors[Index] = vertex_colors[b]; Tpoints[Index] = vertex_positions[b]; Index++;
    Tcolors[Index] = vertex_colors[c]; Tpoints[Index] = vertex_positions[c]; Index++;
    Tcolors[Index] = vertex_colors[a]; Tpoints[Index] = vertex_positions[a]; Index++;
    Tcolors[Index] = vertex_colors[c]; Tpoints[Index] = vertex_positions[c]; Index++;
    Tcolors[Index] = vertex_colors[d]; Tpoints[Index] = vertex_positions[d]; Index++;
}
void idle()
{
	Theta[Axis]+=step;// only one axis is incremented
	if (Theta[Axis]>360.0)
	{Theta[Axis]-=360;}
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	switch(button)
	{
		case GLUT_LEFT_BUTTON: Axis = Xaxis; break;
		case GLUT_MIDDLE_BUTTON: Axis = Yaxis; break;
		case GLUT_RIGHT_BUTTON: Axis =Zaxis; break;
	}
}
void keyboard(unsigned char key, int x, int y)
{
	if(key==' ') step = 0;
	else step = 0.1;
}
