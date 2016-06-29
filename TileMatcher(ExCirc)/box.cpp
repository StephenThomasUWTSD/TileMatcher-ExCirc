#include "box.h"
#include <ctime>
#include <algorithm>
#include "PairsGame.h"
Box::Box(GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat red, GLfloat green, GLfloat blue) : position(0, 0, 0), BVposition(0, 0, 0) {
	x = xPos;
	y = yPos;
	z = zPos;
	r = red;
	g = green;
	b = blue;

	intersect = false;
	BoundSphereRadius = 0.5f;
	BVposition.x = position.x + x;
	BVposition.y = position.y - y;
	BVposition.z = position.z - z;
}

void Box::draw() {
	glutWireCube(1);
}


Box::~Box()
{
}
