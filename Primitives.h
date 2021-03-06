#ifndef __PERIMITIVES_H__
#define __PERIMITIVES_H__

#ifdef _WIN32
#include <Windows.h>
#include <GL/glew.h>
#pragma comment(lib, "glew32.lib")
#endif

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstddef>

namespace lab2 {

typedef struct {
    float x[4];     //Vertex Position
    float c[4];     //Vertex Color
} Vertex;

class Primitive {
protected:
	GLuint vertex_handle;   
	GLuint triangle_handle;
public:
	virtual void draw() =0;
};

class Box : public Primitive {
public:
	Box(float x, float y, float z, float red, float green, float blue);
	void draw();
};

class Cone : public Primitive {
protected:
	int slices, stacks;
public:
	Cone(float bottom_r, float top_r, float height, int slices, int stacks,
	     float red, float green, float blue);
	void draw();
};

class Sphere : public Primitive {
protected:
	int m, n;
public:
	Sphere(float radius, int m, int n, float red, float green, float blue);
	void draw();
};

class SquarePlane : public Primitive {
protected:
	int div;
public:
	SquarePlane(float size, int div, float red, float green, float blue);
	void draw();
};

} // namespace lab2

#endif
