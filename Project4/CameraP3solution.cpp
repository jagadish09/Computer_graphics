#include "CameraP3solution.h"

void PrintN(float& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}


// setModelViewMatrix used in the book "Computer Graphics using OpenGL" Hill/Kelley page 336
void Camera::setModelViewMatrix() {
	float m[16];
	Vector eVec(eye.x, eye.y, eye.z);

	m[0] = u.x;
	m[1] = v.x;
	m[2] = n.x;
	m[3] = 0;
	m[4] = u.y;
	m[5] = v.y;
	m[6] = n.y;
	m[7] = 0;
	m[8] = u.z;
	m[9] = v.z;
	m[10] = n.z;
	m[11] = 0;
	m[12] = -eVec.dot(u);
	m[13] = -eVec.dot(v);
	m[14] = -eVec.dot(n);
	m[15] = 1.0;

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

void Camera::set(float ex, float ey, float ez, float lx, float ly, float lz, float ux, float uy, float uz) {
	Point e(ex, ey, ez);
	Point l(lx, ly, lz);
	Vector y(ux, uy, uz);
	set(e, l, y);
}

// set used in the book "Computer Graphics using OpenGL" Hill/Kelley page 336
void Camera::set(Point& e, Point& l, Vector& y) {
	eye.set(e);
	look.set(l);
	up.set(y);
	n.set(e - l);
	u.set(y.cross(n));
	n.normalize();
	u.normalize();
	v.set(n.cross(u));
	v.normalize();
	setModelViewMatrix();
}
//Change camera to perspective or parallel
void Camera::setShape(float vAng, float asp, float nearD, float farD) {
	float degrees;
	viewAngle = vAng;
	aspect = asp;
	nearDist = nearD;
	farDist = farD;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);

	degrees = ((viewAngle / 2)*pi) / 180;
	H = nearDist*tan(degrees);
	W = H*aspect;

	printf("H:");
	PrintN(H);
	printf("\nW:");
	PrintN(W);
	printf("\n");
}

Vector Camera::GetC(int width, int height, int i, int j) {
	Vector c;

	c.set((n*(nearDist*-1)) + u*(W*((float(2 * i) / float(width)) - 1.0f)) + v*(H*((float(2 * j) / float(height)) - 1.0f)));
	//c.normalize();
	return c;
}

Point Camera::GetEye() {
	return eye;
}


void Camera::roll(float angle){//camera roll function

	Vector c;
	c.set(u);
	float sa = sin(pi / 180 * angle);
	float ca = cos(pi / 180 * angle);


	u.set(ca*c.x + sa*v.x, ca*c.y + sa*v.y, ca*c.z + sa*v.z);
	v.set(-sa*c.x + ca*v.x, -sa*c.y + ca*v.y, -sa*c.z + ca*v.z);
	u.normalize();
	v.normalize();

	setModelViewMatrix();
}

void Camera::pitch(float angle){//camera pitch function
	Vector c;
	c.set(v);
	float sa = sin(pi / 180 * angle);
	float ca = cos(pi / 180 * angle);


	v.set(ca*c.x + sa*n.x, ca*c.y + sa*n.y, ca*c.z + sa*n.z);
	n.set(-sa*c.x + ca*n.x, -sa*c.y + ca*n.y, -sa*c.z + ca*n.z);
	v.normalize();
	n.normalize();

	setModelViewMatrix();
}

void Camera::yaw(float angle){//camera yaw function
	Vector c;
	c.set(n);
	float sa = sin(pi / 180 * angle);
	float ca = cos(pi / 180 * angle);


	n.set(ca*c.x + sa*u.x, ca*c.y + sa*u.y, ca*c.z + sa*u.z);
	u.set(-sa*c.x + ca*u.x, -sa*c.y + ca*u.y, -sa*c.z + ca*u.z);
	n.normalize();
	u.normalize();

	setModelViewMatrix();
}

void Camera::slide(float x, float y, float z){//camera slide function
	float a = x*u.x + y*v.x + z*n.x;
	float b = x*u.y + y*v.y + z*n.y;
	float c = x*u.z + y*v.z + z*n.z;

	look.x += a;
	look.y += b;
	look.z += c;
	eye.x += a;
	eye.y += b;
	eye.z += c;
	setModelViewMatrix();
}