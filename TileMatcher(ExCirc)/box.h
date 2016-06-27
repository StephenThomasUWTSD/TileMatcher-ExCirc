#pragma once
#include "gl\glut.h"
#include "vector.h"

class Box
{
public:
	Box(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~Box();

	void draw(void);
	bool isBoundSphereIntersect(Ray v);
	float randColour();
	GLfloat x, y, z;
	GLfloat r, g, b;
	bool intersect;
	float BoundSphereRadius;
	Vector BVposition;
	Vector position;
};

