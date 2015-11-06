#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <SOIL.h>
#include <string>

using namespace std;

const int X_MAX = 1280, Y_MAX = 960;
const int X_CENTER = X_MAX/2, Y_CENTER = Y_MAX/2;
const float R_SPEED = 1.5;
float cameraAngley = 0;
float cameraAnglex = 0;
float camerax = 0, cameray = 50, cameraz = -300;
float prevX = 0;
float clockangle = 0;
bool clockincrease = true;
bool locked = true;
bool moveForward = false, moveBackward = false, moveRight = false, moveLeft = false, moveUp = false, moveDown = false;
GLuint dTex, cTex, wTex, fTex;

GLuint loadTex(string name, GLint swrap, GLint twrap, GLint minf, GLint magf)
{
	GLuint temptex;
	glGenTextures(1, &temptex);
	glBindTexture(GL_TEXTURE_2D, temptex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, swrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, twrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magf);
	int width, height;
	unsigned char* image = SOIL_load_image(name.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	return temptex;
}

void myInit()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, float(X_MAX)/float(Y_MAX), .5, 2000);
	gluLookAt(0, 50, -400, 0, 50, 100, 0, 1, 0);
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutWarpPointer(X_CENTER, Y_CENTER);
	glutSetCursor(GLUT_CURSOR_NONE);

	dTex = loadTex("crate.jpg", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

	cTex = loadTex("crystal.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);

	wTex = loadTex("wall.png", GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);

	fTex = loadTex("brokenglass.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, .5);
}

void drawCrate(float x, float y, float z)
{
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, -25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 0, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 0, 25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(-25, 0, 25);
	glTexCoord2f(1, 0);
	glVertex3i(-25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, -25);

	glTexCoord2f(0, 1);
	glVertex3i(25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, 25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(25, 50, -25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, 25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, 25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, 25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, -25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, -25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, -25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 50, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 50, -25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, 25);

	glEnd();
	glPopMatrix();
}

void myDisplay()
{
	/*glStencilMask(~0);*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT /*| GL_STENCIL_BUFFER_BIT*/);
	glMatrixMode(GL_MODELVIEW);
	/*glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(1);*/
	/*glDepthMask(false);*/
	glColor3ub(255, 255, 255);
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fTex);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3i(300, 0, 300); 
	glTexCoord2f(0, 1);
	glVertex3i(-300, 0, 300); 
	glTexCoord2f(0, 0);
	glVertex3i(-300, 0, -300); 
	glTexCoord2f(1, 0);
	glVertex3i(300, 0, -300);

	
	
	/*glColor3ub(50, 50, 50);
	glVertex3i(150, 0, 150);
	glVertex3i(150, 0, -200);
	glVertex3i(150, 150, -200);
	glVertex3i(150, 150, 150);

	glVertex3i(-150, 0, 150);
	glVertex3i(-150, 0, -200);
	glVertex3i(-150, 150, -200);
	glVertex3i(-150, 150, 150);

	glVertex3i(150, 0, 150);
	glVertex3i(-150, 0, 150);
	glVertex3i(-150, 150, 150);
	glVertex3i(150, 150, 150);*/
	glEnd();
	glDisable(GL_TEXTURE_2D);
	/*glDepthMask(true);*/
	
	glPopMatrix();

	glPushMatrix();
	glScalef(1, -1, 1);
	/*glStencilFunc(GL_EQUAL, 1, 1);
	glStencilMask(0);*/
	glColor3ub(180, 180, 180);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cTex);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(-100, 0, 0);
	glColor3ub(180, 180, 180);
	glScalef(1, -1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dTex);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, -25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 0, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 0, 25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(-25, 0, 25);
	glTexCoord2f(1, 0);
	glVertex3i(-25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, -25);

	glTexCoord2f(0, 1);
	glVertex3i(25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, 25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(25, 50, -25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, 25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, 25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, 25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 0, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 0, -25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, -25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, -25);

	glTexCoord2f(0, 1);
	glVertex3i(-25, 50, -25);
	glTexCoord2f(1, 1);
	glVertex3i(25, 50, -25);
	glTexCoord2f(1, 0);
	glVertex3i(25, 50, 25);
	glTexCoord2f(0, 0);
	glVertex3i(-25, 50, 25);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	

	glPushMatrix();
	glLoadIdentity();
	glScalef(1, -1, 1);
	glTranslatef(100, 25, 0);
	glColor3ub(0, 180, 0);
	glutSolidSphere(25, 20, 20);
	glPopMatrix();
	/*glDisable(GL_STENCIL_TEST);*/

	
	glColor3ub(255, 255, 255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cTex);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, 50);
	glTexCoord2f(.5, 0);
	glVertex3i(0, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3i(-50, 50, 0);
	glTexCoord2f(0, 1);
	glVertex3i(0, 50, -50);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(100, 25, 0);
	glColor3ub(0, 255, 0);
	
	glutSolidSphere(25, 40, 40);
	glPopMatrix();

	glColor3ub(255, 255, 255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dTex);
	drawCrate(-100, 0, 0);
	glDisable(GL_TEXTURE_2D);
	
	glPushMatrix();
	glLoadIdentity();
	glColor3ub(255, 255, 255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wTex);
	glBegin(GL_QUADS);
	glTexCoord2f(0, .5);
	glVertex3i(300, 0, 300);
	glTexCoord2f(1, .5);
	glVertex3i(-300, 0, 300);
	glTexCoord2f(1, 0);
	glVertex3i(-300, 300, 300);
	glTexCoord2f(0, 0);
	glVertex3i(300, 300, 300);

	glTexCoord2f(0, .5);
	glVertex3i(300, 0, -300);
	glTexCoord2f(1, .5);
	glVertex3i(-300, 0, -300);
	glTexCoord2f(1, 0);
	glVertex3i(-300, 300, -300);
	glTexCoord2f(0, 0);
	glVertex3i(300, 300, -300);

	glTexCoord2f(0, .5);
	glVertex3i(300, 0, -300);
	glTexCoord2f(1, .5);
	glVertex3i(300, 0, 300);
	glTexCoord2f(1, 0);
	glVertex3i(300, 300, 300);
	glTexCoord2f(0, 0);
	glVertex3i(300, 300, -300);

	glTexCoord2f(0, .5);
	glVertex3i(-300, 0, -300);
	glTexCoord2f(1, .5);
	glVertex3i(-300, 0, 300);
	glTexCoord2f(1, 0);
	glVertex3i(-300, 300, 300);
	glTexCoord2f(0, 0);
	glVertex3i(-300, 300, -300);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	/*glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex3i(-300, 300, -300);
	glVertex3i(300, 300, -300);
	glVertex3i(300, 300, 300);
	glVertex3i(-300, 300, 300);
	glEnd();*/
	glPopMatrix();
	
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0, 500, 0);
	glRotatef(clockangle, 0, 0, 1);
	glColor3ub(255, 255, 0);
	glBegin(GL_QUADS);

	glVertex3i(10, -300, 10);
	glVertex3i(10, -300, -10);
	glVertex3i(-10, -300, -10);
	glVertex3i(-10, -300, 10);

	glVertex3i(10, 0, 10);
	glVertex3i(10, 0, -10);
	glVertex3i(-10, 0, -10);
	glVertex3i(-10, 0, 10);

	glVertex3i(10, -300, 10);
	glVertex3i(10, -300, -10);
	glVertex3i(10, 0, -10);
	glVertex3i(10, 0, 10);

	glVertex3i(10, -300, 10);
	glVertex3i(-10, -300, 10);
	glVertex3i(-10, 0, 10);
	glVertex3i(10, 0, 10);

	glVertex3i(-10, -300, 10);
	glVertex3i(-10, -300, -10);
	glVertex3i(-10, 0, -10);
	glVertex3i(-10, 0, 10);

	glVertex3i(10, -300, -10);
	glVertex3i(-10, -300, -10);
	glVertex3i(-10, 0, -10);
	glVertex3i(10, 0, -10);

	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}

void idle(int value)
{
	glMatrixMode(GL_MODELVIEW);
	glutTimerFunc(10, idle, 0);
	glRotatef(1, 0, 1, 0);
	if (clockincrease)
	{

		clockangle += cos(clockangle * 2 * 2.9 * M_PI/360)/2;
		if (clockangle >= 30)
		{
			clockincrease = false;
		}
	}
	else
	{
		clockangle -= cos(clockangle * 2 * 2.9 * M_PI/360)/2;
		if (clockangle <= -30)
		{
			clockincrease = true;
		}
	}
	glutPostRedisplay();
	if (locked)
	{
		glutWarpPointer(X_CENTER, Y_CENTER);
	}
	if (moveForward)
	{
		camerax -= sin(cameraAnglex * 2 * M_PI/360);
		cameraz += cos(cameraAnglex * 2 * M_PI/360);
	}
	if (moveBackward)
	{
		camerax += sin(cameraAnglex * 2 * M_PI/360);
		cameraz -= cos(cameraAnglex * 2 * M_PI/360);
	}
	if (moveRight)
	{
		camerax -= cos(cameraAnglex * 2 * M_PI/360);
		cameraz -= sin(cameraAnglex * 2 * M_PI/360);
	}
	if (moveLeft)
	{
		camerax += cos(cameraAnglex * 2 * M_PI/360);
		cameraz += sin(cameraAnglex * 2 * M_PI/360);
	}
	if (moveUp)
	{
		cameray += 1;
	}
	if (moveDown)
	{
		cameray -= 1;
	}
}

void mouseLook(int x, int y)
{
	if (locked)
	{
	cameraAnglex += float(x - X_CENTER) * R_SPEED * 4 * M_PI/360;
	cameraAngley += -float(y - Y_CENTER) * R_SPEED * 4 * M_PI/360;
	if (cameraAnglex > 360)
	{
		cameraAnglex = cameraAnglex - 360;
	}
	if (cameraAnglex < 0)
	{
		cameraAnglex = cameraAnglex + 360;
	}
	if (cameraAngley > 90)
	{
		cameraAngley = 90;
	}
	else if (cameraAngley < -90)
	{
		cameraAngley = -90;
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPushMatrix();
	/*glLoadIdentity();*/
	glTranslatef(0, 50, -400);
	/*gluLookAt(0, 0, 0, 500 * sin(cameraAnglex), 500 * sin(cameraAngley), 1, 0, 1, 0);*/
	
	glRotatef(cameraAngley, 1, 0, 0);
	glRotatef(cameraAnglex, 0, 1, 0);
	
	glTranslatef(-camerax, -cameray, -cameraz);
	}
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(locked)
		{
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		locked = !locked;
	}
}

void keyPress(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		moveForward = true;
	}
	if (key == 's')
	{
		moveBackward = true;
	}
	if (key == 'd')
	{
		moveRight = true;
	}
	if (key == 'a')
	{
		moveLeft = true;
	}
	if (key == 'e')
	{
		moveUp = true;
	}
	if (key == 'q')
	{
		moveDown = true;
	}
}

void keyRelease(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		moveForward = false;
	}
	if (key == 's')
	{
		moveBackward = false;
	}
	if (key == 'd')
	{
		moveRight = false;
	}
	if (key == 'a')
	{
		moveLeft = false;
	}
	if (key == 'e')
	{
		moveUp = false;
	}
	if (key == 'q')
	{
		moveDown = false;
	}
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH /*| GLUT_STENCIL*/);
	glutInitWindowSize(X_MAX, Y_MAX);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Diamond");
	glutTimerFunc(10, idle, 0);
	glutDisplayFunc(myDisplay);
	glutPassiveMotionFunc(mouseLook);
	glutMouseFunc(mouseClick);
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyPress);
	glutKeyboardUpFunc(keyRelease);
	myInit();
	glutMainLoop();
}