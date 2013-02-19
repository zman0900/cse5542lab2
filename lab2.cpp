#include <iostream>

#include "GlGlut.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "CSE 5542 - Lab 2" << endl;
	cout << "Dan Ziemba, 2013" << endl << endl;
	cout << "Controls:" << endl;
	cout << "\t'f' - move body forward" << endl;
	cout << "\t't' - rotate body CCW" << endl;
	cout << "\t'T' - rotate body CW" << endl;
	cout << "\t'l' - lift left arm, right leg; lower right arm, left leg" << endl;
	cout << "\t'r' - lower left arm, right leg; lift right arm, left leg" << endl;

	lab2::GlGlut g;
	g.start(&argc, argv);

	return 0;
}
