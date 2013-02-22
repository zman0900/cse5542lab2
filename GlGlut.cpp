#include <cmath>

#include "GlGlut.h"

using namespace std;

namespace lab2 {

GlGlut *GlGlut::instance = NULL;

void GlGlut::drawArm(double angle) {
	// Arm upper
	glPushMatrix();
	glRotated(angle, 1., 0., 0.);
	glPushMatrix();
	glTranslated(0., 0., -.025);
	glScaled(1., 1., 2.5);
	skinSphere->draw();
	glPopMatrix();
	// Arm lower
	glTranslated(0., 0., -.05);
	glRotated(angle, 1., 0., 0.);
	glPushMatrix();
	glTranslated(0., 0., -.025);
	glScaled(1., 1., 2.5);
	skinSphere->draw();
	glPopMatrix();
	// Hand
	glTranslated(0., 0., -.055);
	glScaled(.5, .5, 1.);
	skinSphere->draw();
	glPopMatrix();
}

void GlGlut::drawLeg(double angle) {
	// Leg upper
	glPushMatrix();
	glRotated(angle, 1., 0., 0.);
	glPushMatrix();
	glTranslated(0., 0., -.0375);
	glScaled(2., 2., 3.75);
	pantSphere->draw();
	glPopMatrix();
	// Leg lower
	glTranslated(0., 0., -.075);
	glRotated(-1*angle, 1., 0., 0.);
	glPushMatrix();
	glTranslated(0., 0., -.0375);
	glScaled(2., 2., 3.75);
	pantSphere->draw();
	glPopMatrix();
	// Foot
	glTranslated(0., 0., -.080);
	glRotated(90., 1., 0., 0.);
	glTranslated(0., 0., .02);
	glScaled(1., 1., 2.);
	skinSphere->draw();
	glPopMatrix();
}

void GlGlut::drawBlobMan() {
	glPushMatrix();
	// Move forward command
	glTranslated(bodyForwardX, 0., bodyForwardZ);
	// Rotate body command
	glRotated(bodyRotateAngle, 0., 1., 0.);
	// Initial Position
	glTranslated(0., .165, 0.);
	glRotated(-90., 1., 0., 0.);
	// Torso
	glPushMatrix();
	glScaled(5., 1., 1.);
	torso->draw();
	glPopMatrix();
	// Neck
	glPushMatrix(); // For neck, head, arms
	glTranslated(0., 0., .1);
	neck->draw();
	// Head
	glPushMatrix();
	glTranslated(0., 0., .03);
	glScaled(2., 2., 2.);
	skinSphere->draw();
	glPopMatrix();
	// Left Arm
	glPushMatrix();
	glTranslated(-.05, 0., 0.);
	drawArm(-1*armLegAngle);
	glPopMatrix();
	// Right Arm
	glPushMatrix();
	glTranslated(.05, 0., 0.);
	drawArm(-90 - -1*armLegAngle);
	glPopMatrix();
	glPopMatrix(); // End neck, head, arms
	// Left leg
	glPushMatrix();
	glTranslated(-.03, 0., 0.);
	drawLeg(-90 - -1*armLegAngle);
	glPopMatrix();
	// Right leg
	glPushMatrix();
	glTranslated(.03, 0., 0.);
	drawLeg(-1*armLegAngle);
	glPopMatrix();
	// Done
	glPopMatrix();
}

void GlGlut::drawClutter() {
	// Trees
	glPushMatrix();
	glTranslated(-.45, 0., -.45);
	drawTree(treeSpace);
	glPopMatrix();
	glPushMatrix();
	glTranslated(.45, 0., -.45);
	drawTree(0.05 - treeSpace);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-.45, 0., .45);
	drawTree(0.05 - treeSpace);
	glPopMatrix();
	glPushMatrix();
	glTranslated(.45, 0., .45);
	drawTree(treeSpace);
	glPopMatrix();

	// Pile of junk
	glPushMatrix();
	glTranslated(0., .05, 0.);
	lowerBox->draw();
	glTranslated(0., .075, 0.);
	upperBox->draw();
	glTranslated(0., .0625, 0.);
	ball->draw();
	glPopMatrix();
}

void GlGlut::drawTree(float space) {
	glPushMatrix();
	glRotated(-90., 1., 0., 0.);
	treeTrunk->draw();
	glTranslated(.0, 0., 0.1 + space);
	treeTop->draw();
	glPopMatrix();
}

void GlGlut::initBlobMan() {
	armLegAngle = 0;
	bodyRotateAngle = 45;
	bodyForwardX = -0.3;
	bodyForwardZ = 0.3;
	torso = new Cone(.01, .01, .1, 10, 10, 1., 0., 0.);
	neck = new Cone(.01, .01, .01, 10, 2, .788, .576, .541);
	skinSphere = new Sphere(.01, 10, 10, .788, .576, .541);
	pantSphere = new Sphere(.01, 10, 10, 0., 0., 1.);
}

void GlGlut::initClutter() {
	treeTrunk = new Cone(.01, .01, .5, 10, 10, .300, .086, 0.);
	treeTop = new Cone(.05, 0., .5, 20, 10, .078, .482, .110);
	treeSpace = 0.05;
	treeSpaceDir = 1;

	lowerBox = new Box(.1, .1, .1, 0., 1., 0.);
	upperBox = new Box(.05, .05, .05, 0., 1., 0.);
	ball = new Sphere(.0375, 10, 10, 0., 1., 0.);
}

//// Glut callbacks /////
void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	ground->draw();
	drawClutter();
	drawBlobMan();

	glutSwapBuffers();
}

void GlGlut::idle() {
	if (treeSpaceDir && treeSpace >= 0.05) treeSpaceDir = 0;
	else if (!treeSpaceDir && treeSpace <= 0.) treeSpaceDir = 1;
	treeSpace = (treeSpaceDir ? treeSpace + 0.001 : treeSpace - 0.001);
	glutPostRedisplay();
}

void GlGlut::keyboard(unsigned char key, int mousex, int mousey) {
	switch(key) {
		case 3:  // Ctrl-c
		case 27: // Esc
			exit(EXIT_SUCCESS);
			break;
		case 'o':
			glRotated(5., 0., 1., 0.);
			break;
		case 'l':
			armLegAngle += 5;
			if (armLegAngle >= 90) armLegAngle = 90;
			break;
		case 'r':
			armLegAngle -= 5;
			if (armLegAngle <= 0) armLegAngle = 0;
			break;
		case 't':
			if (bodyRotateAngle < 360) bodyRotateAngle += 5;
			else bodyRotateAngle = 0;
			break;
		case 'T':
			if (bodyRotateAngle > 0) bodyRotateAngle -= 5;
			else bodyRotateAngle = 360;
			break;
		case 'f':
			bodyForwardX += 0.01*sin(bodyRotateAngle*(M_PI/180));
			bodyForwardZ += 0.01*cos(bodyRotateAngle*(M_PI/180));
			break;
		default:
			//cout << "unused key: " << (int) key << endl;
			return;
	}
	glutPostRedisplay();
}

void GlGlut::reshape(int w, int h) {
	screen_width = w;
	screen_height = h;

	if (w > h) {
		glViewport((w-h)/2, 0, h, h);
	} else {
		glViewport(0, (h-w)/2, w, w);
	}

	glutPostRedisplay();
}
/////////////////////////

//// Static wrappers ////
void GlGlut::displayWrapper() {
	instance->display();
}

void GlGlut::idleWrapper() {
	instance->idle();
}

void GlGlut::keyboardWrapper(unsigned char key, int mousex, int mousey) {
	instance->keyboard(key, mousex, mousey);
}

void GlGlut::reshapeWrapper(int w, int h) {
	instance->reshape(w, h);
}
/////////////////////////

GlGlut::GlGlut() {
	screen_width = DEF_SCREEN_W;
	screen_height = DEF_SCREEN_H;
}

GlGlut::~GlGlut() {
	// Nothing to do here
}

void GlGlut::setInstance() {
	instance = this;
}

void GlGlut::start(int *argc, char *argv[]) {
	setInstance();

	// Init glut
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow(WINDOW_TITLE);

	// Register callbacks
	glutDisplayFunc(displayWrapper);
	glutKeyboardFunc(keyboardWrapper);
	glutReshapeFunc(reshapeWrapper);

	// Setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90., 1., 0., 4.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0.2, 1., 0., 0., -1., 0., 1., 0.);

	//p = new Sphere(0.9, 10, 10, 0., 1., 0.);
	//p = new Box(.9, .9, .9, 0., 1., 0.);
	//p = new Cone(0., .5, .5, 12, 4, 0., 1., 0.);
	ground = new SquarePlane(1., 20, 1., 1., 1.);
	initBlobMan();
	initClutter();

	// Start
	reshape(screen_width, screen_height);
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}

} // namespace lab2
