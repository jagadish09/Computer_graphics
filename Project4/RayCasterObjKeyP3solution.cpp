#include "RayCasterObj.h"



int  isInShadow(Point s,Vector c, RayCasterObjBuffer& ObjBuffer)  //isInShadow function implementation
{
	RayCasterObjNode* cur;
	int sh;
	float x,y,z, disc;
	

	for (int i = 1; i <= ObjBuffer.Size(); i++) {
		cur = ObjBuffer.GetObj(i);
		s.set(cur->obj.invForm * s);
		c.set(cur->obj.invForm * c);

		x = pow(c.x, 2) + pow(c.y, 2) + pow(c.z, 2);
		y = c.dot(s);
		z = pow(s.x, 2) + pow(s.y, 2) + pow(s.z, 2) - 1;

		disc = pow(y, 2) - (x*z);

		if (disc >= 0)
		{
			sh = 0;
			break;
		}
		else
		{
			sh = 1;
		}
	}
	return sh;
}



void PrintNum(float& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}


void PrintNum(int& n) {
	std::ostringstream oss;
	oss << n;
	std::string s(oss.str());
	std::cout << s;
}



RayCasterObj::RayCasterObj() {
	hide = false;
}


RayCasterObj::RayCasterObj(int t) {
	RayCasterObj();
	type = t;
}


float RayCasterObj::HitTime(Point& s, Vector& c) {
	static Point p;
	static Vector v;
	float A, B, C, discriminant, base, quad, hit1, hit2;

	if (hide) {
		hit1 = -1;
		hit2 = -1;
	}
	else {
		switch (type) {
		case RAYCASTER_SPHERE:

			p.set(invForm * s);
			v.set(invForm * c);

			A = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
			B = v.dot(p);
			C = pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2) - 1;

			discriminant = pow(B, 2) - (A*C);
			if (discriminant > 0) {
				base = -1 * (B / A);
				quad = sqrt(discriminant) / A;

				hit1 = base + quad;
				hit2 = base - quad;
			}
			else {
				hit1 = 0;
				hit2 = 0;
			}

			break;

		}
	}

	if (hit1 > hit2) {
		return hit2;
	}
	else {
		return hit1;
	}
}

Color RayCasterObj::PhongShading(Point& p, Vector& dir, int depth, RayCasterLightBuffer& lights, Color& reflect) {

	//*complete phong shading*/
	
	float xn, yn, zn, nx, ny, nz;
	float pr;
	Vector lightVec, viewVec, normalVec, halfVec, reflectVec;
	Color color;
	RayCasterLightNode* cur=lights.GetLight(1);
	float rad;
	float phong;
	float d[4] = { 0, 0, 0, 0 }, s[4] = { 0, 0, 0, 0 }, g[4] = { 0, 0, 0, 0 };
	color.r = 0; 
	color.g = 0;
	color.b = 0; 
	color.a = 0;
	xn = xForm.matrix.m[12];
	yn = xForm.matrix.m[13];
	zn = xForm.matrix.m[14];
	rad = xForm.matrix.m[0];
	nx = (p.x - xn) / rad;
	ny = (p.y - yn) / rad;
	nz = (p.z - zn) / rad;                   // how to find normal
	normalVec.set(nx, ny, nz);
	normalVec.normalize();
    g[0] = cur->light.ambient[0] * ambient[0];
	g[1] = cur->light.ambient[1] * ambient[1];
	g[2] = cur->light.ambient[2] * ambient[2];
	g[3] = cur->light.ambient[3] * ambient[3];
	for (int i = 1; i <= lights.Size(); i++)
	{
		cur = lights.GetLight(i);


		if (cur->light.type == RAYLIGHT_DIRECTIONAL)               // directional light
		{

			xn = cur->light.location.x - p.x;
			yn = cur->light.location.y - p.y;
			zn = cur->light.location.z - p.z;
			lightVec.set(xn, yn, zn);
			lightVec.normalize();
			pr = lightVec.dot(normalVec);
			if (pr<0)
			{
				pr = 0;
			}
			d[0] += cur->light.diffuse[0]* diffuse[0] *pr;
			d[1] += cur->light.diffuse[1]* diffuse[1] * pr;
			d[2] += cur->light.diffuse[2] * diffuse[2] * pr;
			d[3] += cur->light.diffuse[3] * diffuse[3] *pr;
			xn = -dir.x; yn = -dir.y; zn = -dir.z;
			viewVec.set(xn, yn, zn);
			viewVec.normalize();
			float magl = sqrt(lightVec.x*lightVec.x + lightVec.y*lightVec.y + lightVec.z*lightVec.z);
			float magv = sqrt(viewVec.x*viewVec.x + viewVec.y*viewVec.y + viewVec.z*viewVec.z);
			xn = (viewVec.x + lightVec.x) / (magl + magv);
			yn = (viewVec.y + lightVec.y) / (magl + magv);
			zn = (viewVec.z + lightVec.z) / (magl + magv);
			halfVec.set(xn, yn, zn);
			halfVec.normalize();
			pr = halfVec.dot(normalVec);
			phong = pow(pr, shine);
			s[0] += cur->light.specular[0] * specular[0] * phong;
			s[1] += cur->light.specular[1] * specular[1] * phong;
			s[2] += cur->light.specular[2] * specular[2] * phong;
			s[3] += cur->light.specular[3] * specular[3] * phong;
		}


		if (cur->light.type == RAYLIGHT_POINT)         // Point light
		{
			xn = cur->light.location.x - p.x;
			yn = cur->light.location.y - p.y;
			zn = cur->light.location.z - p.z;
			lightVec.set(xn, yn, zn);
			lightVec.normalize();
			pr = lightVec.dot(normalVec);
			if (pr<0)
			{
				pr = 0;
			}

			d[0] += cur->light.diffuse[0] * diffuse[0] * pr;
			d[1] += cur->light.diffuse[1] * diffuse[1] * pr;
			d[2] += cur->light.diffuse[2] * diffuse[2] * pr;
			d[3] += cur->light.diffuse[3] * diffuse[3] * pr;
			xn = -dir.x; yn = -dir.y; zn = -dir.z;
			viewVec.set(xn, yn, zn);
			viewVec.normalize();

			float magl = sqrt(lightVec.x*lightVec.x + lightVec.y*lightVec.y + lightVec.z*lightVec.z);
			float magv = sqrt(viewVec.x*viewVec.x + viewVec.y*viewVec.y + viewVec.z*viewVec.z);
			xn = (viewVec.x + lightVec.x) / (magl + magv);
			yn = (viewVec.y + lightVec.y) / (magl + magv);
			zn = (viewVec.z + lightVec.z) / (magl + magv);
			halfVec.set(xn, yn, zn);
			halfVec.normalize();

			pr = halfVec.dot(normalVec);
			phong = pow(pr, shine);
			s[0] += cur->light.specular[0] *specular[0] * phong;
			s[1] += cur->light.specular[1] *specular[1]* phong;
			s[2] += cur->light.specular[2] * specular[2]* phong;
			s[3] += cur->light.specular[3] * specular[3]* phong;
		}


		if (cur->light.type == RAYLIGHT_SPOT)          // Spot light
		{
			xn = cur->light.location.x;
			yn = cur->light.location.y;
			zn = cur->light.location.z;
			lightVec.set(xn, yn, zn);
			lightVec.normalize();

			Vector vec;
			vec.x = -lightVec.x;
			vec.y = -lightVec.y;
			vec.z = -lightVec.z;
			vec.set(vec.x, vec.y, vec.z);

			vec.normalize();

			pr = vec.dot(normalVec);
			if (pr<0)
			{
				pr = 0;
			}

			cur->light.angle = DegToRad(cur->light.angle);

			d[0] += cur->light.diffuse[0] * diffuse[0] * pr;
			d[1] += cur->light.diffuse[1] * diffuse[1] * pr;
			d[2] += cur->light.diffuse[2] * diffuse[2] * pr;
			d[3] += cur->light.diffuse[3] * diffuse[3] * pr;
			xn = -dir.x; yn = -dir.y; zn = -dir.z;
			viewVec.set(xn, yn, zn);
			viewVec.normalize();

			float magl = sqrt(lightVec.x*lightVec.x + lightVec.y*lightVec.y + lightVec.z*lightVec.z);
			float magv = sqrt(viewVec.x*viewVec.x + viewVec.y*viewVec.y + viewVec.z*viewVec.z);
			xn = (viewVec.x + lightVec.x) / (magl+magv);
			yn = (viewVec.y + lightVec.y) / (magl+ magv);
			zn = (viewVec.z + lightVec.z) / (magl+magv);
			halfVec.normalize();

			float spl = pow(cos(cur->light.angle), cur->light.exp);
			pr = halfVec.dot(normalVec);
			phong = pow(pr, shine);

			s[0] += cur->light.specular[0]*specular[0]*phong*spl;
			s[1] += cur->light.specular[1]*specular[1]*phong*spl;
			s[2] += cur->light.specular[2]*specular[2]*phong*spl;
			s[3] += cur->light.specular[3]*specular[3]*phong*spl;
		}

		
	}

	color.r = d[0] + reflect.r + s[0] + g[0];
	color.g = d[1] + reflect.g + s[1] + g[1];
	color.b = d[2] + reflect.b + s[2] + g[2];

	return color;

}


void RayCasterObj::SetMaterial(int l, float r, float g, float b, float a) {
	switch (l) {
	case AMBIENT:
		ambient[0] = r;
		ambient[1] = g;
		ambient[2] = b;
		ambient[3] = a;
		break;
	case DIFFUSE:
		diffuse[0] = r;
		diffuse[1] = g;
		diffuse[2] = b;
		diffuse[3] = a;
		break;
	case SPECULAR:
		specular[0] = r;
		specular[1] = g;
		specular[2] = b;
		specular[3] = a;
		break;
	}
}


int RayCasterObjBuffer::Size() {
	return count;
}


int RayCasterObjBuffer::AddObj(int t) {

	if (front == NULL) {
		front = new RayCasterObjNode;
		front->obj.type = t;
		end = front;
	}
	else {
		end->next = new RayCasterObjNode;
		end = end->next;
		end->obj.type = t;
	}
	return ++count;
}


RayCasterObjNode* RayCasterObjBuffer::GetObj(int c) {
	int i;
	RayCasterObjNode* cur;

	if ((c > count) || (c < 1)) {
		return NULL;
	}
	else {
		cur = front;
		for (i = 1; i<c; ++i) {
			cur = cur->next;
		}
		return cur;
	}
}


void RayCasterObjBuffer::HideObj(int c, bool h) {
	RayCasterObjNode* cur;

	if ((c <= count) && (c > 0)) {
		cur = GetObj(c);
		cur->obj.hide = h;
	}
}


Color RayCasterObjBuffer::CastRay(Point& s, Vector& c, int d, RayCasterObjBuffer objBuffer) {
	RayCasterObjNode* cur;
	RayCasterObjNode* closest;
	Point hitpoint;
	float closestHit = -1.0;
	float hit;
	int i;
	Vector nvector, rvector;
	Color recolor,col;
	float xn, yn, zn,rad;
	float nx, ny, nz;

	for (i = 1; i <= count; i++) {
		cur = GetObj(i);
		if (!cur->obj.hide) {
			hit = cur->obj.HitTime(s, c);
			if (((hit > 0.0f) && ((hit < closestHit) || (closestHit <= 0)))) {
				closestHit = hit;
				closest = cur;
				hitpoint = s + c*closestHit;          //hitpoint calculation
				xn = closest->obj.xForm.matrix.m[12];
				yn = closest->obj.xForm.matrix.m[13];
				zn = closest->obj.xForm.matrix.m[14];

				rad = closest->obj.xForm.matrix.m[0];

				nx = (hitpoint.x - xn) / rad;           
				ny = (hitpoint.y - yn) / rad;
				nz = (hitpoint.z - zn) / rad;
				nvector.set(nx, ny, nz);            
				nvector.normalize();

				float q = c.dot(nvector);
				rvector = c - nvector*q*2;

				if (closestHit <= 0)
				{
					return background;
				}
				else
				{
					//hitpoint = s + c*hit;

					if (d == 0 || d == 1 || (shadows == true && isInShadow(hitpoint, c, objBuffer) == 1))//checking for depth and shadows
						return background;
					recolor = CastRay(hitpoint, rvector, d - 1, objBuffer);//recursively calling cast ray for reflection for depth d
					col = closest->obj.PhongShading(s + c*closestHit, c, d, lights, recolor);
					return col;

				}
			}
		}
	}
}


RayCasterLight::RayCasterLight() {
	hide = false;
	angle = 0.0;
	exp = 0.0;
}

int RayCasterLightBuffer::Size() {
	return count;
}


int RayCasterLightBuffer::AddLight(int t) {

	if (front == NULL) {
		front = new RayCasterLightNode;
		front->light.type = t;
		end = front;
	}
	else {
		end->next = new RayCasterLightNode;
		end = end->next;
		end->light.type = t;
	}
	return ++count;
}


RayCasterLightNode* RayCasterLightBuffer::GetLight(int c) {
	int i;
	RayCasterLightNode* cur;

	if ((c > count) || (c < 1)) {
		return NULL;
	}
	else {
		cur = front;
		for (i = 1; i<c; ++i) {
			cur = cur->next;
		}
		return cur;
	}
}


void RayCasterLightBuffer::HideLight(int c, bool h) {
	RayCasterLightNode* cur;

	if ((c <= count) && (c > 0)) {
		cur = GetLight(c);
		cur->light.hide = h;
	}
}