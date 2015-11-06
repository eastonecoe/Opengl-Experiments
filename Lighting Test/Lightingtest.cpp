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

#define GL_CLAMP_TO_EDGE 0x812F

const int X_MAX = 1280, Y_MAX = 960;
const int X_CENTER = X_MAX/2, Y_CENTER = Y_MAX/2;
const float R_SPEED = 1.5;
float cameraAngley = 0;
float cameraAnglex = 0;
float camerax = 0, cameray = 50, cameraz = -300;
float prevX = 0;
int torAngle = 0;
bool locked = true;
bool moveForward = false, moveBackward = false, moveRight = false, moveLeft = false, moveUp = false, moveDown = false;

GLuint sftex, sbtex, sttex, srtex, sltex, sutex;

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
	gluPerspective(45, float(X_MAX)/float(Y_MAX), .5, 6000);
	gluLookAt(0, 50, -400, 0, 50, 100, 0, 1, 0);
	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	
	GLint light_pos[] = { 700, 700, -700, 1};
	GLfloat light_diff[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat light_spec[] = { 0.0, 0.0, 0.0, 1.0};
	glShadeModel(GL_SMOOTH);

	
	glLightiv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutWarpPointer(X_CENTER, Y_CENTER);
	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	sttex = loadTex("cloudySeaTop.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
	sftex = loadTex("cloudySeaFront.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
	srtex = loadTex("cloudySeaRight.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
	sltex = loadTex("cloudySeaLeft.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
	sutex = loadTex("cloudySeaBottom.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
	sbtex = loadTex("cloudySeaBack.png", GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR);
}


void myDisplay()
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat sphere_diff[] = { .5, .5, .5, 1.0};
	GLfloat torus_diff[] = { 1.0, 0, 0, 1.0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diff);
	glTranslatef(0, 50, 0);
	glutSolidTeapot(100);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sttex);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3i(1500, 1500, 1500);
	glTexCoord2d(0, 1);
	glVertex3i(1500, 1500, -1500);
	glTexCoord2d(1, 1);
	glVertex3i(-1500, 1500, -1500);
	glTexCoord2d(1, 0);
	glVertex3i(-1500, 1500, 1500);
	glEnd();
	


	glBindTexture(GL_TEXTURE_2D, sltex);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3i(1500, 1500, 1500);
	glTexCoord2f(1, 0);
	glVertex3i(1500, 1500, -1500);
	glTexCoord2f(1, 1);
	glVertex3i(1500, -1500, -1500);
	glTexCoord2f(0, 1);
	glVertex3i(1500, -1500, 1500);
	glEnd();
	

	glBindTexture(GL_TEXTURE_2D, srtex);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3i(-1500, 1500, 1500);
	glTexCoord2f(0, 0);
	glVertex3i(-1500, 1500, -1500);
	glTexCoord2f(0, 1);
	glVertex3i(-1500, -1500, -1500);
	glTexCoord2f(1, 1);
	glVertex3i(-1500, -1500, 1500);
	glEnd();
	

	glBindTexture(GL_TEXTURE_2D, sbtex);
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3i(-1500, 1500, 1500);
	glTexCoord2d(0, 1);
	glVertex3i(-1500, -1500, 1500);
	glTexCoord2d(1, 1);
	glVertex3i(1500, -1500, 1500);
	glTexCoord2d(1, 0);
	glVertex3i(1500, 1500, 1500);
	
	glEnd();
	glBindTexture(GL_TEXTURE_2D, sftex);
	
	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3i(1500, 1500, -1500);
	glTexCoord2d(1, 0);
	glVertex3i(-1500, 1500, -1500);
	glTexCoord2d(1, 1);
	glVertex3i(-1500, -1500, -1500);
	glTexCoord2d(0, 1);
	glVertex3i(1500, -1500, -1500);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, sutex);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3i(1500, -1500, 1500);
	glTexCoord2f(0, 0);
	glVertex3i(1500, -1500, -1500);
	glTexCoord2f(1, 0);
	glVertex3i(-1500, -1500, -1500);
	glTexCoord2f(1, 1);
	glVertex3i(-1500, -1500, 1500);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glEnable(GL_LIGHTING);
	glTranslatef(700, 700, -700);
	glRotatef(torAngle, 1, 1, 1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, torus_diff);
	glutWireTorus(100, 200, 100, 100);
	glPopMatrix();
	

	glutSwapBuffers();
}

void idle(int value)
{
	glMatrixMode(GL_MODELVIEW);
	glutTimerFunc(10, idle, 0);
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

	torAngle += 1;
	torAngle = torAngle % 360;
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
	glutCreateWindow("Shadow");
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