#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const int X_MAX = 700;
const int Y_MAX = 700;
const int TIMERSEC = 2000;
bool dividers = false;
bool animation = false;
int selectedSet = 0;
float zoom = 1;
float fr = 0, fg = 0, fb = 0;
float br = 1, bg = 1, bb = 1;
struct vert //individual vertex
{
	float x;
	float y;
};
struct tile //data for a tile
{
	vector<char> type; //glBegin types
	vector<vector<vert>> coords; //vertices to go with each type
};

vector<vector<tile>> tilesets; //vector storing each tileset

void createTileset1() //makes tileset 1
{
	vector<tile> tempset;
	tile temp;
	vert tempv;
	vector<vert> tempsetv;

	temp.type.push_back('T');
	tempv.x = 0; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv);
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('T');
	tempv.x = 0; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv);
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('T');
	tempv.x = 0; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 0; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv);
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('T');
	tempv.x = 0; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv);
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	tilesets.push_back(tempset);
}
void createTileset2() // makes tileset2
{
	vector<tile> tempset;
	tile temp;
	vert tempv;
	vector<vert> tempsetv;

	temp.type.push_back('P');
	tempv.x = 0; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 0; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 10; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv);
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('P');
	tempv.x = 10; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 0; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 0; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv);
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	tilesets.push_back(tempset);
}
void createTileset3() //makes tileset 3
{
	vector<tile> tempset;
	tile temp;
	vert tempv;
	float theta;
	vector<vert> tempsetv;

	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 10 * cos(theta); tempv.y = 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 20 - 10 * cos(theta); tempv.y = 20 - 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 20 - 10 * cos(theta); tempv.y = 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 10 * cos(theta); tempv.y = 20 - 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('L');
	tempv.x = 0; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 10; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	tilesets.push_back(tempset);
}
void createTileset4() //makes tileset 4
{
	vector<tile> tempset;
	tile temp;
	float theta;
	vert tempv;
	vector<vert> tempsetv;

	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 10 * cos(theta); tempv.y = 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 20 - 5 * cos(theta); tempv.y = 20 - 5 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 5 * cos(theta); tempv.y = 5 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 20 - 10 * cos(theta); tempv.y = 20 - 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('L');
	tempv.x = 0; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 0; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 20 - 10 * cos(theta); tempv.y = 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 5 * cos(theta); tempv.y = 20 - 5 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 20 - 5 * cos(theta); tempv.y = 5 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('S');
	for (float i = 0; i <= 20; i++)
	{
		theta = i * M_PI/40;
		tempv.x = 10 * cos(theta); tempv.y = 20 - 10 * sin(theta); tempsetv.push_back(tempv);
	}
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('L');
	tempv.x = 20; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 0; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	tilesets.push_back(tempset);
}
void createTileset5() //makes tileset 5
{
	vector<tile> tempset;
	tile temp;
	vert tempv;
	vector<vert> tempsetv;

	temp.type.push_back('T');
	tempv.x = 5; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('T');
	tempv.x = 0; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('T');
	tempv.x = 20; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('T');
	tempv.x = 5; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 10; tempv.y = 10; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('P');
	tempv.x = 5; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 15; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 0; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('P');
	tempv.x = 15; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 15; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 20; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	temp.type.push_back('P');
	tempv.x = 15; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 15; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 20; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 5; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 0; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 20; tempv.y = 15; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	temp.type.push_back('P');
	tempv.x = 0; tempv.y = 5; tempsetv.push_back(tempv);
	tempv.x = 0; tempv.y = 15; tempsetv.push_back(tempv);
	tempv.x = 5; tempv.y = 20; tempsetv.push_back(tempv);
	tempv.x = 15; tempv.y = 20; tempsetv.push_back(tempv);
	temp.coords.push_back(tempsetv); tempsetv.clear();
	tempset.push_back(temp);
	temp.coords.clear(); temp.type.clear(); tempsetv.clear();

	tilesets.push_back(tempset);
}

void createTiles() //tileset generation
{
	createTileset1();
	createTileset2();
	createTileset3();
	createTileset4();
	createTileset5();
}

void myInit(void)
{
	glClearColor(br, bg, bb, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, X_MAX, 0, Y_MAX);
	createTiles();
}

void drawTile(int tileset, int currentTile)
{
	for (int i = 0; i < tilesets[tileset][currentTile].type.size(); i++)
	{
		if (tilesets[tileset][currentTile].type[i] == 'T')
		{
			glBegin(GL_TRIANGLES);
		}
		else if (tilesets[tileset][currentTile].type[i] == 'L')
		{
			glBegin(GL_LINES);
		}
		else if (tilesets[tileset][currentTile].type[i] == 'S')
		{
			glBegin(GL_LINE_STRIP);
		}
		else if (tilesets[tileset][currentTile].type[i] == 'P')
		{
			glBegin(GL_POLYGON);
		}

		for(int j = 0; j < tilesets[tileset][currentTile].coords[i].size(); j++)
		{
			glVertex2f(tilesets[tileset][currentTile].coords[i][j].x, tilesets[tileset][currentTile].coords[i][j].y);
		}
		glEnd();
	}
}

void myDisplay(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(fr, fg, fb);
	for (int i = 0; i < zoom *  X_MAX / 20; i++)
	{
		glPushMatrix();
		for (int j = 0; j < zoom *  Y_MAX / 20; j++)
		{
			
			drawTile(selectedSet, rand()%tilesets[selectedSet].size());
			glTranslatef(0, 20, 0);
		}
		glPopMatrix();
		glTranslatef(20, 0, 0);
		
	}
	glLoadIdentity();
	if (dividers)
	{
		glColor3ub(255, 0, 0);
		glBegin(GL_LINES);
		for (int i = 0; i < zoom *  X_MAX / 20; i++)
		{
			glVertex2i(i * 20, 0);
			glVertex2i(i * 20, zoom * Y_MAX);
			glVertex2i(0, i * 20);
			glVertex2i(zoom * X_MAX, i * 20);
		}
		glEnd();
	}
	glFlush();
}

void processRightMenuEvents(int option) //submenu for turning tile dividers on and off
{
	dividers = !dividers;
	glutPostRedisplay();
}

void processLeftMenuEvents(int option)
{
	if (option == 0)
	{
		animation = !animation;
		if (animation == false)
		{
			glutChangeToMenuEntry(1, "Start Animation", 0);
		}
		else
		{
			glutChangeToMenuEntry(1, "Stop Animation", 0);
		}
	}
}

void processSetSubmenuEvents(int option) //submenu for choosing tilesets
{
	switch(selectedSet)
	{
	case 0: glutChangeToMenuEntry(1, "Triangles", 0); break;
	case 1: glutChangeToMenuEntry(2, "Squares", 1); break;
	case 2: glutChangeToMenuEntry(3, "Arcs", 2); break;
	case 3: glutChangeToMenuEntry(4, "Complex Arcs", 3); break;
	case 4: glutChangeToMenuEntry(5, "Angles", 4); break;
	}
	selectedSet = option;
	switch(selectedSet)
	{
	case 0: glutChangeToMenuEntry(1, "Triangles *", 0); break;
	case 1: glutChangeToMenuEntry(2, "Squares *", 1); break;
	case 2: glutChangeToMenuEntry(3, "Arcs *", 2); break;
	case 3: glutChangeToMenuEntry(4, "Complex Arcs *", 3); break;
	case 4: glutChangeToMenuEntry(5, "Angles *", 4); break;
	}

	glutPostRedisplay();
}

void processZoomSubmenuEvents(int option)
{
	if (option == 0 && zoom <= 6)
	{
		zoom = zoom * 2.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, X_MAX * zoom, 0, Y_MAX * zoom);
		glutPostRedisplay();
	}
	else if (option == 1 && zoom >= .25)
	{
		zoom = zoom / 2.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, X_MAX * zoom, 0, Y_MAX * zoom);
		glutPostRedisplay();
	}
}

void idle (int value)
{
	glutTimerFunc(TIMERSEC, idle, 0);
	if (animation)
	{
		glutPostRedisplay();
	}
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(X_MAX, Y_MAX);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Truchet");
	glutDisplayFunc(myDisplay);

	int setSubmenu = glutCreateMenu(processSetSubmenuEvents);
	
	glutAddMenuEntry("Triangles *", 0);
	glutAddMenuEntry("Squares", 1);
	glutAddMenuEntry("Arcs", 2);
	glutAddMenuEntry("Complex Arcs", 3);
	glutAddMenuEntry("Angles", 4);


	glutCreateMenu(processRightMenuEvents);
	glutAddMenuEntry("Show Dividers", 0);
	glutAddSubMenu("Tile Sets", setSubmenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int zoomSubmenu = glutCreateMenu(processZoomSubmenuEvents);
	glutAddMenuEntry("Increase Density", 0);
	glutAddMenuEntry("Decrease Density", 1);

	glutCreateMenu(processLeftMenuEvents);
	glutAddMenuEntry("Start Animation", 0);
	glutAddSubMenu("Density", zoomSubmenu);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	myInit();
	glutTimerFunc(TIMERSEC, idle, 0);
	glutMainLoop();
}