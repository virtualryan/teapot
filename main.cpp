//Ryan Horvath
//Teapot
//3-12-2005

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <GL/glut.h>

#define PI 3.14159265
#define MOUSE_SENSE .5

int windowW = 640;
int windowH = 480;

static int OLD_X, OLD_Y;
float theta, phi;
float xCoord, yCoord, zCoord;
//static float STEREO_SEPARATION = -.25;

void init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0, 0, 0, 1.0);
	glClearDepth(1.0f);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)windowW/(GLfloat)windowH,0.1f,2000.0f);
	glMatrixMode(GL_MODELVIEW);	
	glEnable(GL_COLOR_MATERIAL);
	
	//*************************************
	// Initialize lighting
	//*************************************
	GLfloat light_pos0[] = {0, 20, 40};
	GLfloat light_pos1[] = {0, 20, 20};
	GLfloat light_pos2[] = {0, 20, 0};
	GLfloat light_pos3[] = {0, 20, -20};
	GLfloat light_ambient[] = {0.25, 0.25, 0.25, 0.25};
	GLfloat light_diffuse[] = {0.25, 0.25, 0.25, 0.25};
	GLfloat light_specular[] = {0.25, 0.25, 0.25, 0.25};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
		
//	lcdInitialize();
	glutFullScreen();
}


void draw_scene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);	
	//glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glLoadIdentity();
	glTranslatef(0,-2,0);
	glRotatef(phi, 1, 0, 0);
	glRotatef(theta, 0, 1, 0);
	glTranslatef(xCoord, yCoord, zCoord);
	
/* if (!lcdIsLeft())
    glTranslatef(1.1*STEREO_SEPARATION, 0, 0);

else
	glTranslatef(-1.1*STEREO_SEPARATION, 0, 0);
  */
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	
        glPushMatrix();
	glTranslatef(0,0,-10);
	glColor3f(0.8,0.0,0.0);
	glutWireTeapot(1);

	glPopMatrix();
	
//	lcdSwitchLens();
	glutSwapBuffers();

}


void reshape(int w, int h)		
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,2000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
	
	windowW = w;
	windowH = h;
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:	exit(0);
				break;

	case 'w':	zCoord+=2*cos(theta*2*PI/360.0);
				xCoord-=2*sin(theta*2*PI/360.0);
				break;

	case 's':	zCoord-=2*cos(theta*2*PI/360.0);
				xCoord+=2*sin(theta*2*PI/360.0);
				break;

	case 'a':	zCoord+=2*sin(theta*2*PI/360.0);
				xCoord+=2*cos(theta*2*PI/360.0);
				break;

	case 'd':	zCoord-=2*sin(theta*2*PI/360.0);
				xCoord-=2*cos(theta*2*PI/360.0);
				break;
	}
	glutPostRedisplay();
}

void mouse(int x, int y)
{
	theta += (x - OLD_X) * MOUSE_SENSE;
     phi += (y - OLD_Y) * MOUSE_SENSE;
      if (phi>90)phi=90;
	if (phi<-90)phi=-90;
	if (theta>360)theta-=360;
	if (theta<0)theta+=360;                                                                          
                                                                        
        OLD_X = x;
        OLD_Y = y;
                                                                                
        glutPostRedisplay();

	
}

void mouse_button(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON){
	  if (state == GLUT_DOWN){
		  OLD_X=x;
	  	  OLD_Y=y;}}
}

int main (int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("The Hangar");
	init();
	glutDisplayFunc(draw_scene);
	//glutIdleFunc(draw_scene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouse);
	glutMouseFunc(mouse_button);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();
	return 0;
}
