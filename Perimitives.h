#ifndef __PERIMITIVES_H__
#define __PERIMITIVES_H__

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

namespace lab2 {

typedef struct {
    float x[4];     //Vertex Position
    float c[4];     //Vertex Color
} Vertex;

class Sphere {
protected:
	int m, n;
	GLuint vertex_handle;   
	GLuint triangle_handle;
public:
	Sphere(float radius, int _m, int _n, float red, float green, float blue);
	void draw();
};

} // namespace lab2

#endif
