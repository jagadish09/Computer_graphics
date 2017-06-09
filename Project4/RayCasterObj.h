#ifndef RAYCASTEROBJ_H
#define RAYCASTEROBJ_H

#include "Matrix.h"

#define RAYCASTER_SPHERE 0
#define RAYCASTER_PLANE 1

#define RAYLIGHT_GLOBALAMBIENT 0
#define RAYLIGHT_POINT 1
#define RAYLIGHT_DIRECTIONAL 2
#define RAYLIGHT_SPOT 3

#define AMBIENT 4
#define DIFFUSE 5
#define SPECULAR 6

class RayCasterObjBuffer;

class Color {
public:
	float r, g, b, a;

	Color() { r = 0.0; g = 0.0; b = 0.0; a = 1; }
};


class RayCasterLight {
public:
	Point location;
	Vector direction;
	//float r,g,b,a;
	float ambient[4]; //r,g,b,a
	float diffuse[4]; //r,g,b,a
	float specular[4]; //r,g,b,a
	float tmp;
	float exp;
	float cutoff;
	float angle;
	int type;
	bool hide;

	RayCasterLight();
};

//Linked list of lights
class RayCasterLightNode {
public:
	RayCasterLightNode* next;
	RayCasterLight light;

	RayCasterLightNode() { next = NULL; }

};

//Maintain and work on the lights list
class RayCasterLightBuffer {
private:
	int count;

public:
	RayCasterLightBuffer() { count = 0; front = NULL; end = NULL; }

	RayCasterLightNode* front;
	RayCasterLightNode* end;

	int Size();

	int AddLight(int);
	RayCasterLightNode* GetLight(int);
	void HideLight(int, bool);
};

//objects in the ray caster world, spheres only incorporated currently
class RayCasterObj {
public:
	bool hide;
	int type;
	Transform xForm;
	Matrix invForm;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shine;
	Color objColor;


	RayCasterObj();
	RayCasterObj(int t);

	float DegToRad(float theta) { float PI = 3.14159; return (theta* PI / 180); }
	float HitTime(Point&, Vector&);
	Color PhongShading(Point&, Vector&, int, RayCasterLightBuffer&, Color&);
	void SetMaterial(int, float, float, float, float);
};

//Linked list of objects in the ray caster world
class RayCasterObjNode {
public:
	RayCasterObjNode() { next = NULL; }

	RayCasterObjNode* next;
	RayCasterObj obj;
};

//handle the object list/buffer
class RayCasterObjBuffer {
private:
	int count;

public:
	RayCasterLightBuffer lights;
	Color background;
	bool shadows=false;

	RayCasterObjBuffer() { background.r = .8f; background.g = .8f; background.b = .8f; background.a = 1; count = 0; front = NULL; end = NULL; }

	RayCasterObjNode* front;
	RayCasterObjNode* end;

	int Size();

	int AddObj(int);
	RayCasterObjNode* GetObj(int);
	void HideObj(int, bool);

	Color CastRay(Point&, Vector&, int d, RayCasterObjBuffer);
};

#endif