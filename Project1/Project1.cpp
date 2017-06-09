
#include "stdafx.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>



void myInit(void) {

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800.0, 0, 800.0);
}




void myDisplay(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	
	int i = 100;
	while (i <= 500)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2i(i, 100);
		glVertex2i(i, 600);
		glEnd();
		i += 10;
	}
	i = 100;
	while (i <= 600)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2i(100, i);
		glVertex2i(500, i);
		glEnd();
		i += 10;
	}

	glBegin(GL_QUADS);
	glColor3f(0.36, 0.25, 0.20);
	glVertex2f(280, 580);
	glVertex2f(280, 550);
	glVertex2f(327, 537);
	glVertex2f(327, 580);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.36, 0.25, 0.20);
	glVertex2f(304, 590);
	glVertex2f(313, 590);
	glVertex2f(315, 585);
	glVertex2f(327, 583);
	glVertex2f(327, 580);
	glVertex2f(300, 580);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex2f(327, 570);
	glVertex2f(340, 565);
	glVertex2f(350, 560);
	glVertex2f(353, 550);
	glVertex2f(348, 540);
	glVertex2f(327, 537);

	glVertex2f(280, 550);
	glVertex2f(266, 560);
	glVertex2f(264, 566);
	glVertex2f(263, 574);
	glVertex2f(270, 578);
	glVertex2f(280, 580);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(340, 472);
	glVertex2f(280, 473);
	glVertex2f(277, 430);
	glVertex2f(278, 425);
	glVertex2f(283,420);
	glVertex2f(320,375);
	glVertex2f(322,420);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(350, 350);
	glVertex2f(320,375);
	glVertex2f(280,403);
	glVertex2f(245,415);
	glVertex2f(202,415);
	glVertex2f(182,410);
	glVertex2f(160,390);

	glVertex2f(150,360);
	glVertex2f(165,325);
	glVertex2f(190,305);
	glVertex2f(230,310);
	
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(202,415);
	glVertex2f(182,410);
	glVertex2f(167,435);
	glVertex2f(160,477);
	glVertex2f(175,477);
	glVertex2f(190,475);
	glVertex2f(200,465);

	glVertex2f(202,415);


	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(167, 435);
	glVertex2f(160, 477);
	glVertex2f(142, 455);
	glVertex2f(125, 405);
	glVertex2f(127,355);

	glVertex2f(150,380);


	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(340,472);
	glVertex2f(322,420);
	glVertex2f(338,377);
	glVertex2f(350,350);
	glVertex2f(352,380);


	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(350,350);
	glVertex2f(350,250);
	glVertex2f(380,215);
	glVertex2f(452,190);


	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(350, 350);
	glVertex2f(230,310);
	glVertex2f(250,300);
	glVertex2f(350,250);


	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(250, 300);
	glVertex2f(240, 290);
	glVertex2f(262, 258);
	glVertex2f(267,273);


	glEnd();

	glBegin(GL_POLYGON);
	
	glVertex2f(267, 273);
	glVertex2f(250, 300);
	glVertex2f(350,250);
	glVertex2f(295,255);
	glEnd();

	glBegin(GL_POLYGON);

	glVertex2f(322,238);
	glVertex2f(295, 255);
	glVertex2f(290,240);
	glVertex2f(315, 155);
	glVertex2f(335, 115);
	glVertex2f(320, 225);
	
	glEnd();
	
	glBegin(GL_TRIANGLES);
	glVertex2f(280, 550);
	glVertex2f(282, 545);
	glVertex2f(327,537);

	glVertex2f(360, 520);
	glVertex2f(340,472);
	glVertex2f(385,495);

	glVertex2f(283, 420);
	glVertex2f(280, 403);
	glVertex2f(320,375);

	glVertex2f(320,375);
	glVertex2f(338,377);
	glVertex2f(350,350);

	glVertex2f(350, 250);
	glVertex2f(322,238);
	glVertex2f(295,255);

	glVertex2f(360, 190);
	glVertex2f(335,168);
	glVertex2f(352,165);

	glEnd();
	
	glBegin(GL_QUADS);
	glVertex2f(282, 545);
	
	glVertex2f(250, 520);
	glVertex2f(275, 518);
	glVertex2f(327, 537);
	
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(250, 520);

	glVertex2f(250, 510);
	glVertex2f(255, 500);
	glVertex2f(275, 518);


	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(210, 280);

	glVertex2f(230, 310);
	glVertex2f(190, 305);
	glVertex2f(180,290);


	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(350,350);

	glVertex2f(370, 365);
	glVertex2f(365, 380);
	glVertex2f(352,380);


	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(315, 155);

	glVertex2f(310,140);
	glVertex2f(317,120);
	glVertex2f(335,115);

	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(350, 250);

	glVertex2f(360,245);
	glVertex2f(360, 190);
	glVertex2f(352, 165);

	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(352, 165);
	glVertex2f(340, 155);

	glVertex2f(350, 145);
	glVertex2f(452, 190);

	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(380,215);
	glVertex2f(360, 190);
	glVertex2f(352, 165);
	glVertex2f(452, 190);



	glEnd();


	glBegin(GL_QUAD_STRIP);
	
	glVertex2f(275, 518);
	glVertex2f(255, 500);

	glVertex2f(295, 497);
	glVertex2f(280, 473);
	glVertex2f(360, 520);
	glVertex2f(340, 472);

	glEnd();

	glBegin(GL_QUAD_STRIP);

	glVertex2f(165,325);
	glVertex2f(190,305);

	glVertex2f(134,300);
	glVertex2f(170,300);
	glVertex2f(132,288);
	glVertex2f(180, 290);
	glVertex2f(175,277);
	glVertex2f(210,280);

	glEnd();

	glBegin(GL_QUAD_STRIP);


	glVertex2f(175, 277);
	glVertex2f(210, 280);
	glVertex2f(170,260);
	glVertex2f(200,260);

	glVertex2f(217,213);
	glVertex2f(235,215);
	glVertex2f(220,195);
	glVertex2f(230,190);

	glEnd();

	glBegin(GL_QUAD_STRIP);


	glVertex2f(210,280);
	glVertex2f(200,260);
	glVertex2f(228, 270);

	glVertex2f(215, 258);
	glVertex2f(230,238);
	glVertex2f(213,250);

	glEnd();

	glFlush();


}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("HW1");

	myInit();

	glutDisplayFunc(myDisplay);

	glutMainLoop();
}