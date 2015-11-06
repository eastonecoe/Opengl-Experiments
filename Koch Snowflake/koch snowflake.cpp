#include <windows.h>   // use as needed for your system
#include <gl/Gl.h>
#include <gl/glu.h>
#include <math.h>
#include <glut.h>
#include <iostream>

const float pi = 3.14159265358979;
const int TIMERSEC = 3000;
int currentgen = 7;
const int maxgen = 7;
const bool SPIRAL = true;

using namespace std;

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);      // set the bg color to a bright white
	glMatrixMode(GL_PROJECTION);// set up appropriate matrices- to be explained 
	glLoadIdentity();// to be explained
	gluOrtho2D(0.0, 1800.0, 0.0, 1800.0);// to be explained
}

void drawKochCurve( int n, GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 )
// draws an nth generation Koch Curve between points (x1,y1) and (x2, y2)
{
	double xtemp1, xtemp2;
	double ytemp1, ytemp2;
	double theta, distance;
	if (n == 0)
	{
    glBegin(GL_LINE_STRIP);
		glVertex2f( x1, y1);     
		glVertex2f( x2, y2);     
	glEnd();
	}
	else
	{
		xtemp1 = ((x2 - x1)/3) + x1;
		ytemp1 = ((y2 - y1)/3) + y1;
		xtemp2 = ((x2 - x1)* 2/3) + x1;
		ytemp2 = ((y2 - y1)* 2/3) + y1;
		if (!SPIRAL)
		{
		theta = atan2(ytemp2 - ytemp1, xtemp2 - xtemp1) - (60 * 2 * pi/360);
		}
		else
		{
			theta = atan2(ytemp2 - ytemp1, xtemp2 - xtemp1) - (60 * 2 * pi/360) - pi;
		}
		distance = sqrt((pow(((x2 - x1)/3),2) + pow(((y2 - y1)/3),2)));

		/*glBegin(GL_LINES);
		glVertex2f( x1, y1);
		glVertex2f( xtemp1, ytemp1 );
		glVertex2f( xtemp2, ytemp2 );
		glVertex2f( x2, y2); 
		glEnd();*/
		drawKochCurve( n-1, x1, y1, xtemp1, ytemp1);
		drawKochCurve( n-1, xtemp2, ytemp2, x2, y2);
		drawKochCurve( n-1, xtemp1, ytemp1, xtemp1 + distance * cos(theta), ytemp1 + distance * sin(theta));
		drawKochCurve( n-1, xtemp1 + distance * cos(theta), ytemp1 + distance * sin(theta), xtemp2, ytemp2);
	}
}

void drawKochSnowflake( int n )
// draws an nth generation Koch Snowflake
{
	int x[4], y[4];
	int scale = 300;
	int translate = 350;
	float angle = pi/2.0;
	for (int i = 0; i < 3; i++)
	{
		x[i] = cos(angle)*scale + translate;
		y[i] = sin(angle)*scale + translate;
		angle += 2*pi/3;
	}
	x[3] = x[0];
	y[3] = y[0];

	for (int i = 0; i < 3; i++)
	{
		drawKochCurve( n, x[i], y[i], x[i+1], y[i+1] );
	}
}

void idle(int value)
{
	glutTimerFunc(TIMERSEC, idle, 0);
	/*currentgen++;
	currentgen = currentgen % maxgen;
	glutPostRedisplay();*/
}

 void myDisplay(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-800, -400, 0);
	for (int j = 0; j < 5; j++)
	{
		glPushMatrix();
		for (int i = 0; i < 5; i++)
		{
			 // clear the screen 
		glPushMatrix();
		glColor3ub(255,0,0);
		drawKochSnowflake( currentgen );
		glTranslatef(sqrt(3.0)/2 * 300, 850, 0);
		glScalef(1, -1, 1);
		glColor3ub(255,255,255);
		drawKochSnowflake( currentgen);
		glPopMatrix();
		glTranslatef(sqrt(3.0) * 300, 0, 0);
		}
		glPopMatrix();
		glTranslatef((sqrt(3.0) * 300/2) * pow(-1.0,j), 450, 0);
	}



	
	glFlush();		                 // send all output to display 
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	glutInitWindowSize(700,700);     // set the window size
	glutInitWindowPosition(100, 150); // set the window position on the screen
	glutCreateWindow("Koch Snowflake"); // open the screen window(with its exciting title)
	glutDisplayFunc(myDisplay);     // register the redraw function
	myInit();                   
	glutTimerFunc(TIMERSEC, idle, 0);
	glutMainLoop(); 		     // go into a perpetual loop
}
