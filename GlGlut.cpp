#include "GlGlut.h"

using namespace std;

namespace lab2 {

GlGlut *GlGlut::instance = NULL;

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
}

void GlGlut::drawTree(float space) {
	glPushMatrix();
	glRotated(-90., 1., 0., 0.);
	treeTrunk->draw();
	glTranslated(.0, 0., 0.1 + space);
	treeTop->draw();
	glPopMatrix();
}

void GlGlut::initClutter() {
	treeTrunk = new Cone(.01, .01, .5, 10, 10, .300, .086, 0.);
	treeTop = new Cone(.05, 0., .5, 20, 10, .078, .482, .110);
	treeSpace = 0.05;
	treeSpaceDir = 1;
}

//// Glut callbacks /////
void GlGlut::display() {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	ground->draw();
	drawClutter();

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
	initClutter();

	// Start
	reshape(screen_width, screen_height);
	glutIdleFunc(idleWrapper);
	glutMainLoop();
}

} // namespace lab2
