
#include "GL/glut.h" 


#include <string>

#include <iostream>

#include <fstream>

#include <strstream>

using namespace std;



#include <windows.h> 
#include <assert.h>

#include <math.h>

#include <stdlib.h>

#include <gl/Gl.h>

#include <gl/Glu.h>

#include "GL/glut.h"
#include<math.h>


double scalelen = 0.5;
double rotAngle = 1;
static double anglex = 0;
static double angley = 0;
static double anglez = 0;
static int xa, ya, za = 0;
static double sx = 1;
static double sy = 1;
static double sz = 1;
static int tx=0,ty=0,tz = 0,b=0,v=0;
int translatex=1,translatez=1,translatey = 1;

static char omy = 'o';


void draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);


	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();



	glutSwapBuffers();

}
void my()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	double scale[16] = { sx,0,0,0,0,sy,0,0,0,0,sz,0,0,0,0,1 };
	double translate[16] = { 1,0,0,tx,0,1,0,ty,0,0,1,tz,0,0,0,1 };
	glMultMatrixd(scale);
	if (xa == 1)
	{
		double rotate[16]= { 1,0,0,0,0,cos(anglex),-sin(anglex),0,0,sin(anglex),cos(anglex),0,0,0,0,1 };
		glMultMatrixd(rotate);
	}
	else if (ya == 1)
	{
		double rotate[16] = { cos(angley),0,sin(angley),0,0,1,0,0,-sin(angley),0,cos(angley),0,0,0,0,1 };
		glMultMatrixd(rotate);

	}
	else
	{
		if (za == 1)
		{

			double rotate[16] = { cos(anglez),-sin(anglez),0,0,sin(anglez),cos(anglez),0,0,0,0,1,0,0,0,0,1 };
			glMultMatrixd(rotate);
		}
	}
	
	glMultMatrixd(translate);
	draw();

}

void displayObjects(void)

{



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	if (b==1)
	glPushMatrix();
	

		glScaled(sx,sy,sz);
	if (xa == 1)
	{
		glRotated(anglex, 1, 0, 0);
	}
	else if (ya == 1)
	{
		glRotated(angley, 0, 1, 0);
	}
	else 
		if (za==1)
			glRotated(anglez, 0, 0, 1);
	glTranslatef(tx,ty,tz);
	draw();
}

void init() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0.0, 0.0, 70.0, 0.0, 0.0, -6.0, 0.0, 1.0, 0.0);
	glTranslatef(0, 0, -6.0f);
	draw();


}


void keyboard(unsigned char k, int x, int y)
{
	if (omy == 'o')
	{
		xa = 0;
		ya = 0;
		za = 0;
		sx = 1;
		sy = 1;
		sz = 1;
		tx = 0;
		ty = 0;
		tz = 0;
		anglex = 0;
		angley = 0;
		anglez = 0;
		b = 0;
		v = 0;
		switch (k)
		{
		case 'q':
			anglex -= rotAngle;
			xa = 1;
			break;
		case 'w':
			anglex += rotAngle;
			xa = 1;
			break;
		case 'a':
			angley -= rotAngle;
			ya = 1;
			break;
		case 's':
			angley += rotAngle;
			ya = 1;
			break;
		case 'z':
			anglez -= rotAngle;
			za = 1;
			break;
		case 'x':
			anglez += rotAngle;
			za = 1;
			break;
		case '4':
			sx = scalelen;
			break;
		case '6':
			sx = 1 + scalelen;
			break;
		case '2':
			sy = scalelen;
			break;
		case '8':
			sy = 1 + scalelen;
			break;
		case '5':
			sz = scalelen;
			break;
		case '9':
			sz = 1 + scalelen;
			break;
		case '+':
			sx += scalelen;
			sy += scalelen;
			sz += scalelen;
			break;
		case '-':
			sx -= scalelen;
			sy -= scalelen;
			sz -= scalelen;
			break;
		case 'y':
			ty += translatey;
			break;
		case 'h':
			ty -= translatey;
			break;
		case 'g':
			tx -= translatex;
			break;
		case 'j':
			tx += translatex;
			break;
		case '1':
			tz += translatez;
			break;
		case '0':
			tz -= translatey;
			break;
		case 'r':
			glLoadIdentity();
			sx = 1;
			sy = 1;
			sz = 1;
			anglex = 0;
			angley = 0;
			anglez = 0;
			tx = 0;
			ty = 0;
			tz = 0;
			gluLookAt(0.0, 0.0, 70.0, 0.0, 0.0, -6.0, 0.0, 1.0, 0.0);
			glTranslatef(0, 0, -6.0f);
		case 'b':
			b = 1;
			break;
		case 'v':
			//v = 1;
			glPopMatrix();
			break;
		case 'm':
			omy = 'm';
			cout<<omy;
			break;
		case 'M':
			omy = 'm';
			//cout << omy;
			break;
		}

		glutPostRedisplay();
	}
	else
	{
		xa = 0;
		ya = 0;
		za = 0;
		sx = 1;
		sy = 1;
		sz = 1;
		tx = 0;
		ty = 0;
		tz = 0;
		anglex = 0;
		angley = 0;
		anglez = 0;
		b = 0;
		v = 0;

			switch (k)
			{
			case 'q':
				anglex -= rotAngle;
				xa = 1;
				break;
			case 'w':
				anglex += rotAngle;
				xa = 1;
				break;
			case 'a':
				angley -= rotAngle;
				ya = 1;
				break;
			case 's':
				angley += rotAngle;
				ya = 1;
				break;
			case 'z':
				anglez -= rotAngle;
				za = 1;
				break;
			case 'x':
				anglez += rotAngle;
				za = 1;
				break;
			case '4':
				sx = scalelen;
				break;
			case '6':
				sx = 1 + scalelen;
				break;
			case '2':
				sy = scalelen;
				break;
			case '8':
				sy = 1 + scalelen;
				break;
			case '5':
				sz = scalelen;
				break;
			case '9':
				sz = 1 + scalelen;
				break;
			case '+':
				sx += scalelen;
				sy += scalelen;
				sz += scalelen;
				break;
			case '-':
				sx -= scalelen;
				sy -= scalelen;
				sz -= scalelen;
				break;
			case 'y':
				ty += translatey;
				break;
			case 'h':
				ty -= translatey;
				break;
			case 'g':
				tx -= translatex;
				break;
			case 'j':
				tx += translatex;
				break;
			case '1':
				tz += translatez;
				break;
			case '0':
				tz -= translatey;
				break;
			case 'r':
				glLoadIdentity();
				sx = 1;
				sy = 1;
				sz = 1;
				anglex = 0;
				angley = 0;
				anglez = 0;
				tx = 0;
				ty = 0;
				tz = 0;
				gluLookAt(0.0, 0.0, 70.0, 0.0, 0.0, -6.0, 0.0, 1.0, 0.0);
				glTranslatef(0, 0, -6.0f);
			case 'b':
				b = 1;
				break;
			case 'v':
				//v = 1;
				glPopMatrix();
				break;
			case 'M' || 'm':
				omy = 'm';
				break;
			case 'o':
				omy = 'o';
				break;
			case 'O':
				omy = 'o';
				break;
		}
		
		my();
	}
}

void main(int argc, char **argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1000, 1000);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("project2");
	init();
	glutDisplayFunc(displayObjects);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

}


