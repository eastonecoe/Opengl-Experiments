#include <windows.h>
#include <iostream>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>

#define PERPECTIVE_PROJECTION 1
#define PARALLEL_PROJECTION   2
#define NEAR_INITIAL    5.0
#define FAR_INITIAL    100.0
#define WIDTH_INITIAL    500
#define HEIGHT_INITIAL   500
#define AXIS_LENGTH 10
#define ROTATION_INCREMENT 1.0
#define EYE_INCREMENT .1


int projection = PERPECTIVE_PROJECTION;
int width = WIDTH_INITIAL;
int height = HEIGHT_INITIAL;  // display window width & height
float nearClip = NEAR_INITIAL;
float farClip = FAR_INITIAL;
float angle = 0;
float camerax = 0, cameray = 0, cameraz = 0;


void reshape (int w, int h);

void myInit(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

void drawHouse( void )
// draws the house in Figure 6.24 (Foley et al, p. 243)
{
   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

   glBegin(GL_LINES);
   glColor3ub(255, 0, 0);
   glVertex3i(8, 8, 42);
   glVertex3i(8 + AXIS_LENGTH, 8, 42);
   glColor3ub(0, 255, 0);
   glVertex3i(8, 8, 42);
   glVertex3i(8, 8 + AXIS_LENGTH, 42);
   glColor3ub(0, 0, 255);
   glVertex3i(8, 8, 42);
   glVertex3i(8, 8, 42 + AXIS_LENGTH);
   glEnd();

   glTranslatef(8, 0, 42);
   glRotatef(angle, 0, 1, 0);
   glTranslatef(-8, 0, -42);

   glColor3ub(255, 255, 255);
   // front pentagon
   glBegin( GL_POLYGON );
     glVertex3f( 0, 0, 54 );
     glVertex3f( 16, 0, 54 );
     glVertex3f( 16, 10, 54 );
     glVertex3f( 8, 16, 54 );
     glVertex3f( 0, 10, 54 );
   glEnd();

   // back pentagon
   glBegin( GL_POLYGON );
     glVertex3f( 0, 0, 30 );
     glVertex3f( 0, 10, 30 );
     glVertex3f( 8, 16, 30 );
     glVertex3f( 16, 10, 30 );
     glVertex3f( 16, 0, 30 );
   glEnd();

   // right side rectangle
   glBegin( GL_POLYGON );
     glVertex3f( 16, 0, 54 );
     glVertex3f( 16, 0, 30 );
     glVertex3f( 16, 10, 30 );
     glVertex3f( 16, 10, 54 );
   glEnd();

   // left side rectangle
   glBegin( GL_POLYGON );
     glVertex3f( 0, 0, 54 );
     glVertex3f( 0, 10, 54 );
     glVertex3f( 0, 10, 30 );
     glVertex3f( 0, 0, 30 );
   glEnd();

   // right side roof rectangle
   glBegin( GL_POLYGON );
     glVertex3f( 16, 10, 54 );
     glVertex3f( 16, 10, 30 );
     glVertex3f( 8, 16, 30 );
     glVertex3f( 8, 16, 54 );
   glEnd();

   // left side roof rectangle
   glBegin( GL_POLYGON );
     glVertex3f( 0, 10, 54 );
     glVertex3f( 8, 16, 54 );
     glVertex3f( 8, 16, 30 );
     glVertex3f( 0, 10, 30 );
   glEnd();

   // bottom rectangle
   glBegin( GL_POLYGON );
     glVertex3f( 0, 0, 54 );
     glVertex3f( 0, 0, 30 );
     glVertex3f( 16, 0, 30 );
     glVertex3f( 16, 0, 54 );
   glEnd();
}

void drawFrontView( void )
{
   //  draw front view in lower left
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (projection == PERPECTIVE_PROJECTION)
     glFrustum (-10.0, 10.0, -10.0, 10.0, nearClip, farClip);
   else
     glOrtho (-20.0, 20.0, -20.0, 20.0, nearClip, farClip);

   glViewport (0, 0, (GLsizei) width/2, (GLsizei) height/2); 

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (8.0 + camerax, 8.0 + cameray, 65.0 + cameraz, 8.0, 8.0, 54.0, 0.0, 1.0, 0.0);
   drawHouse();
   glFlush ();
}

void drawRightSideView( void )
{
    glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (projection == PERPECTIVE_PROJECTION)
     glFrustum (-10.0, 10.0, -10.0, 10.0, nearClip, farClip);
   else
     glOrtho (-20.0, 20.0, -20.0, 20.0, nearClip, farClip);

   glViewport ((GLsizei) width/2, 0, (GLsizei) width/2, (GLsizei) height/2); 

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (30 + camerax, 8.0 + cameray, 42 + cameraz, 8.0, 8.0, 42, 0.0, 1.0, 0.0);
   drawHouse();
   glFlush ();
}

void drawTopView( void )
{
    glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (projection == PERPECTIVE_PROJECTION)
     glFrustum (-10.0, 10.0, -10.0, 10.0, nearClip, farClip);
   else
     glOrtho (-20.0, 20.0, -20.0, 20.0, nearClip, farClip);

   glViewport (0, (GLsizei) height/2, (GLsizei) width/2, (GLsizei) height/2); 

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (8.0 + camerax, 30.0 + cameray, 42 + cameraz, 8.0, 8.0, 42, 0.0, 0.0, 1.0);
   drawHouse();
   glFlush ();
}

void drawOffAxesView( void )
{
    glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   if (projection == PERPECTIVE_PROJECTION)
     glFrustum (-10.0, 10.0, -10.0, 10.0, nearClip, farClip);
   else
     glOrtho (-20.0, 20.0, -20.0, 20.0, nearClip, farClip);

   glViewport ((GLsizei) width/2, (GLsizei) height/2, (GLsizei) width/2, (GLsizei) height/2); 

   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (20.0 + camerax, 20.0 + cameray, 60 + cameraz, 8.0, 8.0, 42.0, 0.0, 1.0, 0.0);
   drawHouse();
   glFlush ();
}

void myDisplay(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // z-buffering
   glColor3f (1.0, 1.0, 1.0);

   drawFrontView();
   drawTopView();
   drawRightSideView();
   drawOffAxesView();
}

void reshape (int w, int h)
{
   width = w;
   height = h;
}

void processRightMenuEvents(int option) 
{
	projection = option;
	reshape(width, height);
	glutPostRedisplay();
}

void processKeyEvents(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1': angle -= ROTATION_INCREMENT; break;
	case '2': angle += ROTATION_INCREMENT; break;
	case 's': cameraz += EYE_INCREMENT; break;
	case 'w': cameraz -= EYE_INCREMENT; break;
	case 'a': camerax -= EYE_INCREMENT; break;
	case 'd': camerax += EYE_INCREMENT; break;
	case 'e': cameray += EYE_INCREMENT; break;
	case 'q': cameray -= EYE_INCREMENT; break;
	}
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<main>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)

{
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH ); // z-buffering
    glutInitWindowSize( WIDTH_INITIAL, HEIGHT_INITIAL );
    glutInitWindowPosition( 100, 100 );
    glutCreateWindow( "house" );
	glEnable( GL_DEPTH_TEST );
    myInit();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(processKeyEvents);

	glutCreateMenu(processRightMenuEvents);
	glutAddMenuEntry("perspective", PERPECTIVE_PROJECTION);
	glutAddMenuEntry("parallel", PARALLEL_PROJECTION);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop( );

	return 0;
}