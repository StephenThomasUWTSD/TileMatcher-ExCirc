#include "vector.h"
#include <stdlib.h>
//#include "gl/glut.h"
#include "gl\glut.h"

#include "house.h"
#include <math.h>
#include <iostream>
using namespace std;
void init(void);
void display(void);
void drawHouse(void);
House myhouse;
static int theta = 0;

int winview[2]; //contains window view width [0] and height [1]
float aspect = 1.0;
float near = 1.0;
float far = 20.0;
float fov = 60;
       double WorldT[16];
   double objectNear[4];
    double objectFar[4];


void init(void)
{
        WorldT[0] = 1; WorldT[4] = 0;WorldT[8] = 0;WorldT[12] = 0;
		WorldT[1] = 0; WorldT[5] = 1;WorldT[9] = 0;WorldT[13] = 0;
		WorldT[2] = 0; WorldT[6] = 0;WorldT[10] = 1;WorldT[14] = 0;
		WorldT[3] = 0; WorldT[7] = 0;WorldT[11] = 0;WorldT[15] = 1;
   GLfloat mat_specular[] = { 0.256777, 0.137622, 0.086014, 1.0 };
   GLfloat mat_diffuse[] = { 0.7083, 0.27048, 0.0828, 1.0 };
   GLfloat mat_ambient[] = { 0.79125, 0.6735, 0.6225, 1.0 };
   GLfloat mat_shininess[] = { 12.8 };

   GLfloat light_position[] = { 5.0, -5.0, 5.0, 0.0 };

   glClearColor (0.0, 0.0, 0.0, 0.0);  //reset "empty" background colour
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

    glutInitDisplayMode(GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
}

void keyboardread(unsigned char key, int x,int y)
{
	switch (key) {
	case 'r':
			theta = (theta + 10)% 360;
			glutPostRedisplay();
			cout<<theta<<endl;
			break;
	case 'l':
			theta = (theta - 10)% 360;
			glutPostRedisplay();
			break;
	}
}

	


void drawHouse(void)
	{
    myhouse.draw();
}
void display(void)
{
//select clearing background colour
//if you don't do this then OGL will display
//whatever was last drawn in the buffer
//make it black
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0,1.0,1.0);
   glLoadIdentity();//reset transformation (of modelview matrix)

   gluLookAt(5.0*sin(float(theta)*0.0175), 5.0, 5.0*cos(float(theta)*0.0175), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
   //  place camera - it rotates about the origin, on y = 5.0 plane,
   // with a radius of 5.0; 0,0,0 - aim lens towards 0,0,0; 
   //  0,1,0 - the up vector defines an unique orientation
   glGetDoublev(GL_MODELVIEW_MATRIX,WorldT);//get for use with gluUnproject	
	glBegin(GL_TRIANGLES);  //fire ray
    glNormal3f(0.0,-1.0,0.0);     
	    glVertex3d(objectNear[0],objectNear[1],objectNear[2]);
	    glVertex3d(objectFar[0],objectFar[1],objectFar[2]);
	    glVertex3d(objectNear[0]+0.1,objectNear[1],objectNear[2]);

	glEnd();

   drawHouse();
    glPushMatrix();
    glTranslatef(1.0,0.0,0.0);
    drawHouse();
    glPopMatrix();
    glPushMatrix(); 
    glTranslatef(3.0,0.0,-1.0);
    glRotatef(90.0,0.0,1.0,0.0);
    drawHouse();
	glPopMatrix();
	//glutWireCube(1.0);
	//glFlush();
	  glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0); 
//             l,r,bot,top,near,far

	glMatrixMode(GL_MODELVIEW);
	   winview[0]=w; winview[1] = h;

}
void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		int view[4];
		//   double modelview[16];
		double proj[16];
		glGetIntegerv(GL_VIEWPORT, view);
		glGetDoublev(GL_PROJECTION_MATRIX, proj);
		int realy = view[3] - (GLint)y - 1;
		int check = gluUnProject(x, realy, -1, WorldT, proj, view, objectNear, objectNear + 1, objectNear + 2);
		cout << "unprojected near co-ords are ";
		for (int i = 0; i<4; i++) {
			cout << objectNear[i] << " ";
		} cout << "\n";
		check = gluUnProject(x, realy, 1, WorldT, proj, view, objectFar, objectFar + 1, objectFar + 2);
		cout << "unprojected far co-ords are ";
		for (int i = 0; i<4; i++) {
			cout << objectFar[i] << " ";
		} cout << "\n";
		//prepare for collision test by making a ray
		Vector d(objectFar[0], objectFar[1], objectFar[2]);
		Vector p(objectNear[0], objectNear[1], objectNear[2]);
		Ray ray1;  //this is the ray cast
		ray1.SetOrigin(p);      //initialise ray with origin and direction vector
		ray1.SetDirection(d - p);
		if (myhouse.isBoundSphereIntersect(ray1))
			cout << "hit" << endl;
		else
			cout << "miss" << endl;


		glutPostRedisplay();

	}
}
   
int main(int argc, char** argv)
{
	  glutInit(&argc,argv);
	  glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB);
	  glutInitWindowSize(800,800);
	  glutInitWindowPosition(100,100);
	  glutCreateWindow("3D house");
	  init();
	  glutReshapeFunc(reshape);
	  glutDisplayFunc(display);
	  glutKeyboardFunc(keyboardread);
      glutMouseFunc(mouse);

	  glutMainLoop();
	  return 0;
}