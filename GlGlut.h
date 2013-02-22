#ifndef __GLGLUT_H__
#define __GLGLUG_H__

#include <cstdlib>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#include "Primitives.h"

#define DEF_SCREEN_W 800
#define DEF_SCREEN_H 800
#define WINDOW_TITLE "CSE 5542 Lab 2 - Dan Ziemba"

namespace lab2 {

class GlGlut {
private:
	Primitive *ball, *ground, *lowerBox, *treeTrunk, *treeTop, *upperBox;
	Primitive *torso, *neck, *skinSphere, *pantSphere;
	float treeSpace;
	int treeSpaceDir;
	int armLegAngle;
	int bodyRotateAngle;
	float bodyForwardX, bodyForwardZ;
	int animationEnabled;
	int armLegAngleInc;  // Only used for auto animation
	int firstPerson;
	double distPerStep;

	void drawArm(double angle);
	void drawBlobMan();
	void drawClutter();
	void drawLeg(double angle);
	void drawTree(float space);
	void initBlobMan();
	void initClutter();
	void updateCamera();
protected:
	static GlGlut *instance;
	int screen_width;
	int screen_height;
	
	// Glut callbacks
	void display();
	void idle();
	void keyboard(unsigned char key, int mousex, int mousey);
	void mouseClick(int button, int state, int x, int y);
	void reshape(int w, int h);

	////  Static wrappers used to register glut callbacks
	static void displayWrapper();
	static void idleWrapper();
	static void keyboardWrapper(unsigned char key, int mousex, int mousey);
	static void reshapeWrapper(int w, int h);
public:
	GlGlut();
	~GlGlut();

	// Called by start to make wrappers work
	void setInstance();
	// Starts scene, does not return
	void start(int *argc, char *argv[]);
};

} // namespace lab2

#endif
