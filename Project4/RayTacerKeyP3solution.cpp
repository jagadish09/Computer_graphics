
#include <windows.h>

#include <string>
#include "CameraP3solution.h"
#include "RayCasterObj.h"
#include <GL/glut.h>


#define GL 0
#define CASTER 1
static int depth = 3;
int const screenWidth = 640;
int const screenHeight = 480;
int const pixelCount = screenWidth * screenHeight;
double const winHt = 1.0;

int Drawing = CASTER;
int clickActionX, clickActionY;
float tmp = 0.0;
bool initComplete = false;
static int projection = 0;

//inbetween small sphere
GLfloat mat_ambient1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat mat_diffuse1[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_specular1[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat mat_shininess1[] = { 3.0f };

//matte medium sphere
GLfloat mat_ambient2[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat mat_diffuse2[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat mat_specular2[] = { 0.001f, 0.001f, 0.001f, 1.0f };
GLfloat mat_shininess2[] = { 1.0f };

//shiny large sphere
GLfloat mat_ambient3[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
GLfloat mat_diffuse3[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
GLfloat mat_specular3[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat mat_shininess3[] = { 89.6f };


RayCasterObjBuffer objBuffer;
Camera cam;
int resolution = 1;

void MyDisplay();

void PrintNm(float& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}


void PrintNm(int& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}


void ResetCamera() {

	cam.set(0, 0, 1, 0, 0, 0, 0.0, 1.0, 0.0);
	MyDisplay();
}







void DrawRaster() {
	Vector c;
	Color color;
	float pixelCount;
	int i, j, curPixel, copyPixel;

	pixelCount = screenWidth*screenHeight;

	float* pixels = new float[pixelCount * 3];

	for (j = 0; j<screenHeight; ++j) { //loop through all pixels
		for (i = 0; i<screenWidth; ++i) {
			curPixel = ((j*screenWidth) + i) * 3;

			if (j%resolution == 0) {
				if (i%resolution == 0) {
					c.set(cam.GetC(screenWidth, screenHeight, i, j));
					if (projection == 0)
					{
						
						color = objBuffer.CastRay(cam.GetEye(), c, depth, objBuffer); //finding hit point and shading for the pixel
					}

					else//setting up orthographic projection
					{
						float A = c.x + cam.GetEye().x;
						float B= c.y + cam.GetEye().y;
						float C= c.z + cam.GetEye().z;
						Point s1;
						s1.set(A, B, C);
						Vector c1;
						c1.set(0, 0, -1);
						color = objBuffer.CastRay(s1, c1, depth, objBuffer);
					}
				}
				else {
					copyPixel = curPixel - 3;
					color.r = pixels[copyPixel];
					color.g = pixels[copyPixel + 1];
					color.b = pixels[copyPixel + 2];
				}
			}
			else {
				copyPixel = curPixel - (screenWidth * 3);
				color.r = pixels[copyPixel];
				color.g = pixels[copyPixel + 1];
				color.b = pixels[copyPixel + 2];
			}

			pixels[curPixel] = color.r;
			pixels[curPixel + 1] = color.g;
			pixels[curPixel + 2] = color.b;
		}
	}
	glDrawPixels(screenWidth, screenHeight, GL_RGB, GL_FLOAT, pixels);
}


void setOpenGLMaterials() {


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);

	glPushMatrix();
	glTranslated(0.125, -0.25, -1);
	glutSolidSphere(0.125, 50, 50);
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);

	glPushMatrix();
	glTranslated(0.5, 0.5, -1.75);
	glutSolidSphere(0.375, 50, 50);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient3);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular3);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess3);

	glPushMatrix();
	glTranslated(-0.5, 0, -2.5);
	glutSolidSphere(0.75, 50, 50);
	glPopMatrix();
}

void MyDisplay() {

	if (initComplete) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (Drawing == GL) {
			setOpenGLMaterials(); //DRAW USING OPENGL SHADING METHODS
			glFlush();
		}
		else {
			DrawRaster(); //DRAW USING RAY TRACING METHODS
		}

		glutSwapBuffers();
	}
}




void setRayTracingMaterials() {
	int sphere1 = objBuffer.AddObj(RAYCASTER_SPHERE);
	objBuffer.GetObj(sphere1)->obj.xForm.Translate(0.125, -0.25, -1);
	objBuffer.GetObj(sphere1)->obj.xForm.Scale(0.125, 0.125, 0.125);
	objBuffer.GetObj(sphere1)->obj.invForm = objBuffer.GetObj(sphere1)->obj.xForm.matrix.Inverse();
	objBuffer.GetObj(sphere1)->obj.SetMaterial(AMBIENT, 0.5, 0.5, 0.5, 1.0);
	objBuffer.GetObj(sphere1)->obj.SetMaterial(DIFFUSE, 0.7, 0.7, 0.7, 1.0);
	objBuffer.GetObj(sphere1)->obj.SetMaterial(SPECULAR, 0.9, 0.9, 0.9, 1.0);
	objBuffer.GetObj(sphere1)->obj.shine = 3.0f;
	objBuffer.GetObj(sphere1)->obj.objColor.r = 1.0;
	objBuffer.GetObj(sphere1)->obj.objColor.g = 0.0;
	objBuffer.GetObj(sphere1)->obj.objColor.b = 0.0;

	int sphere2 = objBuffer.AddObj(RAYCASTER_SPHERE);
	objBuffer.GetObj(sphere2)->obj.xForm.Translate(0.5, 0.5, -1.75);
	objBuffer.GetObj(sphere2)->obj.xForm.Scale(0.375, 0.375, 0.375);
	objBuffer.GetObj(sphere2)->obj.invForm = objBuffer.GetObj(sphere2)->obj.xForm.matrix.Inverse();
	objBuffer.GetObj(sphere2)->obj.SetMaterial(AMBIENT, 0.5, 0.5, 0.5, 1.0);
	objBuffer.GetObj(sphere2)->obj.SetMaterial(DIFFUSE, 0.9, 0.9, 0.9, 1.0);
	objBuffer.GetObj(sphere2)->obj.SetMaterial(SPECULAR, 0.001, 0.001, 0.001, 1.0);
	objBuffer.GetObj(sphere2)->obj.shine = 1.0f;
	objBuffer.GetObj(sphere2)->obj.objColor.r = 0.0;
	objBuffer.GetObj(sphere2)->obj.objColor.g = 1.0;
	objBuffer.GetObj(sphere2)->obj.objColor.b = 0.0;

	int sphere3 = objBuffer.AddObj(RAYCASTER_SPHERE);
	objBuffer.GetObj(sphere3)->obj.xForm.Translate(-0.5, 0, -2.5);
	objBuffer.GetObj(sphere3)->obj.xForm.Scale(0.75, 0.75, 0.75);
	objBuffer.GetObj(sphere3)->obj.invForm = objBuffer.GetObj(sphere3)->obj.xForm.matrix.Inverse();
	objBuffer.GetObj(sphere3)->obj.SetMaterial(AMBIENT, 0.23125, 0.23125, 0.23125, 1.0);
	objBuffer.GetObj(sphere3)->obj.SetMaterial(DIFFUSE, 0.2775, 0.2775, 0.2775, 1.0);
	objBuffer.GetObj(sphere3)->obj.SetMaterial(SPECULAR, 0.1, 0.1, 0.1, 1.0);
	objBuffer.GetObj(sphere3)->obj.SetMaterial(SPECULAR, 0.7, 0.7, 0.7, 1.0);
	objBuffer.GetObj(sphere3)->obj.shine = 9.0f;
	objBuffer.GetObj(sphere3)->obj.objColor.r = 0.0;
	objBuffer.GetObj(sphere3)->obj.objColor.g = 0.0;
	objBuffer.GetObj(sphere3)->obj.objColor.b = 1.0;
}

void setObjectMaterials() {
	setRayTracingMaterials();
}

void setOpenGLLighting() {

	GLfloat none[] = { 0.0f,0.0f,0.0f,1.0f };

	//global ambient light
	GLfloat globalambient[] = { 0.15f, 0.05f, 0.05f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalambient);

	//POINT light
	GLfloat light_position0[] = { 200.0f, 100.0f, 50.0f, 1.0f };
	GLfloat lightIntensity0[] = { 0.65f, 0.65f, 0.65f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, none);
	glLightfv(GL_LIGHT0, GL_SPECULAR, none);

	//blue spot light
	GLfloat light_position1[] = { -1.0f,0.0f,0.0f,1.0f };
	GLfloat light_direction1[] = { 0.0f, 0.0f, -1.0f };
	GLfloat lightIntensity1[] = { 0.4f, 0.4f, 0.7f, 1.0f };

	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_direction1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
	glLightfv(GL_LIGHT1, GL_AMBIENT, none);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, none);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightIntensity1);



	//yellow DIRECTIONAL light
	GLfloat light_position2[] = { -400.0f, 692.0f, 0.0f, 0.0f };
	GLfloat lightIntensity2[] = { 0.8f, 0.8f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, none);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightIntensity2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, none);


}
void setRayTracingLighting() {
	//this function sets up the lighting properties for ray tracing
	int globalAmbientLight = objBuffer.lights.AddLight(RAYLIGHT_GLOBALAMBIENT);
	objBuffer.lights.GetLight(globalAmbientLight)->light.ambient[0] = 0.25f;
	objBuffer.lights.GetLight(globalAmbientLight)->light.ambient[1] = 0.05f;
	objBuffer.lights.GetLight(globalAmbientLight)->light.ambient[2] = 0.05f;
	objBuffer.lights.GetLight(globalAmbientLight)->light.ambient[3] = 1.00f;


	//POINT LIGHT
	int light1 = objBuffer.lights.AddLight(RAYLIGHT_POINT);
	objBuffer.lights.GetLight(light1)->light.location.set(200, 100, 50);
	objBuffer.lights.GetLight(light1)->light.ambient[0] = 0.65f;
	objBuffer.lights.GetLight(light1)->light.ambient[1] = 0.65f;
	objBuffer.lights.GetLight(light1)->light.ambient[2] = 0.65f;
	objBuffer.lights.GetLight(light1)->light.ambient[3] = 1.00f;

	objBuffer.lights.GetLight(light1)->light.diffuse[0] = 0.00f;
	objBuffer.lights.GetLight(light1)->light.diffuse[1] = 0.00f;
	objBuffer.lights.GetLight(light1)->light.diffuse[2] = 0.00f;
	objBuffer.lights.GetLight(light1)->light.diffuse[3] = 1.00f;

	objBuffer.lights.GetLight(light1)->light.specular[0] = 0.00f;
	objBuffer.lights.GetLight(light1)->light.specular[1] = 0.00f;
	objBuffer.lights.GetLight(light1)->light.specular[2] = 0.00f;
	objBuffer.lights.GetLight(light1)->light.specular[3] = 1.00f;

	//BLUE SPOT LIGHT
	int light2 = objBuffer.lights.AddLight(RAYLIGHT_SPOT);
	objBuffer.lights.GetLight(light2)->light.location.set(-1.0, 0.0, 1.0);
	objBuffer.lights.GetLight(light2)->light.direction.set(0.0, 0.0, -1.0);
	objBuffer.lights.GetLight(light2)->light.angle = 30.0f;
	objBuffer.lights.GetLight(light2)->light.exp = 0.5f;

	objBuffer.lights.GetLight(light2)->light.ambient[0] = 0.00f;
	objBuffer.lights.GetLight(light2)->light.ambient[1] = 0.00f;
	objBuffer.lights.GetLight(light2)->light.ambient[2] = 0.00f;
	objBuffer.lights.GetLight(light2)->light.ambient[3] = 1.00f;

	objBuffer.lights.GetLight(light2)->light.diffuse[0] = 0.00f;
	objBuffer.lights.GetLight(light2)->light.diffuse[1] = 0.00f;
	objBuffer.lights.GetLight(light2)->light.diffuse[2] = 0.00f;
	objBuffer.lights.GetLight(light2)->light.diffuse[3] = 1.00f;

	objBuffer.lights.GetLight(light2)->light.specular[0] = 0.4f;
	objBuffer.lights.GetLight(light2)->light.specular[1] = 0.4f;
	objBuffer.lights.GetLight(light2)->light.specular[2] = 0.7f;
	objBuffer.lights.GetLight(light2)->light.specular[4] = 1.00f;

	//YELLOW DIRECTIONAL LIGHT
	int light3 = objBuffer.lights.AddLight(RAYLIGHT_DIRECTIONAL);
	objBuffer.lights.GetLight(light3)->light.location.set(-400.0, 692.0, 0.0);

	objBuffer.lights.GetLight(light3)->light.ambient[0] = 0.00f;
	objBuffer.lights.GetLight(light3)->light.ambient[1] = 0.00f;
	objBuffer.lights.GetLight(light3)->light.ambient[2] = 0.00f;
	objBuffer.lights.GetLight(light3)->light.ambient[3] = 1.00f;

	objBuffer.lights.GetLight(light3)->light.diffuse[0] = 0.8f;
	objBuffer.lights.GetLight(light3)->light.diffuse[1] = 0.8f;
	objBuffer.lights.GetLight(light3)->light.diffuse[2] = 0.6f;
	objBuffer.lights.GetLight(light3)->light.diffuse[3] = 1.00f;

	objBuffer.lights.GetLight(light3)->light.specular[0] = 0.00f;
	objBuffer.lights.GetLight(light3)->light.specular[1] = 0.00f;
	objBuffer.lights.GetLight(light3)->light.specular[2] = 0.00f;
	objBuffer.lights.GetLight(light3)->light.specular[3] = 1.00f;
}

void setLighting() {
	setOpenGLLighting();
	setRayTracingLighting();
}

//keyboard function
void keyfunc(unsigned char k, int x, int y)
{
	printf("%d", k);
	if (k == 43)//for increasing depth
	{
		depth = depth + 1;
	}
	else if (k == 45)//for decreasing depth
	{
		
			depth = depth - 1;
	}
	else if (k == 115)//for shadows
		{
			if (objBuffer.shadows == false)
				objBuffer.shadows = true;
			else
				objBuffer.shadows = false;
		}
	else if (k == 111)//orthographic projection
	{
			projection = 1;
	}
	else if (k == 112)//perspective projection
	{
		projection = 0;
	}

	else if (k == 53)//slide up
	{
		cam.slide(0, 1, 0);
	}
	else if (k == 55)//slide down
	{
		cam.slide(0, -1, 0);
	}
	else if (k == 57)//slide left
	{
		cam.slide(-1, 0, 0);
	}
	else if (k == 48)//slide right
	{
		cam.slide(1, 0, 0);
	}
	else if (k == 113)//slide forward
	{
		cam.slide(0, 0, -1);
	}
	else if (k == 97)//slide backward
	{
		cam.slide(0, 0, 1);
	}
	else if (k == 52)//roll left
	{
		cam.roll(-10);
	}
	else if (k == 54)//roll right
	{
		cam.roll(10);
	}
	else if (k == 56)//pitch up
	{
		cam.pitch(10);
	}
	else if (k == 50)//pitch down
	{
		cam.pitch(-10);
	}
	else if (k == 49)//yaw left
	{
		cam.yaw(10);
	}
	else if (k == 51)//yaw right
	{
		cam.yaw(-10);
	}

	glutPostRedisplay();
}

void main(int argc, CHAR *argv) {
	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(250, 50);
	glutCreateWindow("Ray Casting!");

	glClearColor(0.5 * 0.25, 0.5 * 0.05, 0.5 * 0.05, 1.0); //for opengl use only
	glColor3f(0.0, 0.0, 0.0);

	Color backGround;
	backGround.r = 0.5;
	backGround.g = 0.5;
	backGround.b = 0.5;
	objBuffer.background = backGround;

	glPointSize(1.0);
	glLineWidth(1.0);


	glutKeyboardFunc(keyfunc);

	setObjectMaterials();
	setLighting();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, screenWidth, screenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-winHt*screenWidth / screenHeight, winHt*screenWidth / screenHeight, -winHt, winHt, 0.1, 200.0);

	cam.setShape(30.0f, float(screenWidth) / float(screenHeight), 1.0f, 200.0f);
	ResetCamera();

	
	printf("depth%d", depth);
	glutDisplayFunc(MyDisplay);

	initComplete = true;
	glutMainLoop();
}