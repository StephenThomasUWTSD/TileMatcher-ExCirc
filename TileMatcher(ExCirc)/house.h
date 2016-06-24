//whilst it is desireable to let a bounding volume "own" its object, it is
//possible to conceive the opposite view, i.e. an object (house in this case)
//has a bounding volume as an attribute.  Typically, physics engines attach 
//an object to a bounding volume and all physics is done "to" the bounding volume.

#include "vector.h"
#ifndef HOUSE_H
#define HOUSE_H
class House {
public:
	House();
	bool isBoundSphereIntersect(Ray v);
	void draw();

private:
    bool intersect;
	float BoundSphereRadius;
    Vector position; //point
	Vector BVposition;//point
};

#endif

/*
House::House() : position(0,0,0),BVposition(0,0,0){
	intersect = false;
	BoundSphereRadius=1.0;
	BVposition.x=position.x+ 0.5;
	BVposition.y=position.y- 0.25;
	BVposition.z=position.z- 0.5;
}
bool House::isBoundSphereIntersect(Ray v){
   //calc collision
	cout<<"line point distance squared is: "<<v.LinePointDistanceSqd(BVposition)<<"\n";
	
 
  if (v.LinePointDistanceSqd(BVposition)>(BoundSphereRadius*BoundSphereRadius))
	   return false; //no intersection detected
  else true;//intersection detected
}
*/
