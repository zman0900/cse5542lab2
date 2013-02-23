#include "Primitives.h"

using namespace std;

namespace lab2 {

Box::Box(float x, float y, float z, float red, float green, float blue) {
	Vertex *v = new Vertex[8];
	float px=x/2., nx=-px, py=y/2., ny=-py, pz=z/2., nz=-pz;
	//// Front
	// up left
	v[0].x[0] = nx;
	v[0].x[1] = py;
	v[0].x[2] = nz;
	v[0].x[3] = 1.;
	// up right
	v[1].x[0] = px;
	v[1].x[1] = py;
	v[1].x[2] = nz;
	v[1].x[3] = 1.;
	// down left
	v[2].x[0] = nx;
	v[2].x[1] = ny;
	v[2].x[2] = nz;
	v[2].x[3] = 1.;
	// down right
	v[3].x[0] = px;
	v[3].x[1] = ny;
	v[3].x[2] = nz;
	v[3].x[3] = 1.;
	//// Back
	// up left
	v[4].x[0] = nx;
	v[4].x[1] = py;
	v[4].x[2] = pz;
	v[4].x[3] = 1.;
	// up right
	v[5].x[0] = px;
	v[5].x[1] = py;
	v[5].x[2] = pz;
	v[5].x[3] = 1.;
	// down left
	v[6].x[0] = nx;
	v[6].x[1] = ny;
	v[6].x[2] = pz;
	v[6].x[3] = 1.;
	// down right
	v[7].x[0] = px;
	v[7].x[1] = ny;
	v[7].x[2] = pz;
	v[7].x[3] = 1.;

	// Color
	for (int i=0; i<8; i++) {
		v[i].c[0] = red;
		v[i].c[1] = green;
		v[i].c[2] = blue;
		v[i].c[3] = 1.;
	}

	// Triangles
	GLuint *t = new GLuint[36];  // Two per face
	// Front
	t[0] = 0;
	t[1] = 1;
	t[2] = 3;
	t[3] = 0;
	t[4] = 3;
	t[5] = 2;
	// Left
	t[6] = 4;
	t[7] = 0;
	t[8] = 2;
	t[9] = 4;
	t[10] = 2;
	t[11] = 6;
	// Right
	t[12] = 1;
	t[13] = 5;
	t[14] = 7;
	t[15] = 1;
	t[16] = 7;
	t[17] = 3;
	// Back
	t[18] = 5;
	t[19] = 4;
	t[20] = 6;
	t[21] = 5;
	t[22] = 6;
	t[23] = 7;
	// Top
	t[24] = 4;
	t[25] = 5;
	t[26] = 1;
	t[27] = 4;
	t[28] = 1;
	t[29] = 0;
	// Bottom
	t[30] = 2;
	t[31] = 3;
	t[32] = 7;
	t[33] = 2;
	t[34] = 7;
	t[35] = 6;

	glGenBuffers(1, &vertex_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*8, v, GL_STATIC_DRAW);

	glGenBuffers(1, &triangle_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*36, t, GL_STATIC_DRAW);

	delete[] v;
	delete[] t;
}

void Box::draw() {
	//Inform OpenGL which handles to use
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	//Enable the arrays on the client side
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// number of coordinates per vertex (4 here),  coordinate value format,
	// stride between consecutive vertices, and pointers to the first coordinate
	glVertexPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, x)));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, c)));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Now we are ready to draw, using the triangle indices in the buffer
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT,
	               reinterpret_cast<void*>(0));

	//Disable the arrays on the client side
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

Cone::Cone(float bottom_r, float top_r, float height, int _slices, int _stacks,
	     float red, float green, float blue) {
	slices = _slices;
	stacks = _stacks;

	#define radius(z) ((bottom_r)-((z)/((height)/((bottom_r)-(top_r)))))

	Vertex *v = new Vertex[slices*(stacks+1)];
	for (int i=0; i<=stacks; i++) {
		float z = i * (height/(float)stacks);
		for (int j=0; j<slices; j++) {
			float theta = (j*2*M_PI)/slices;
			v[i*slices+j].x[0] = radius(z) * cos(theta);
			v[i*slices+j].x[1] = radius(z) * sin(theta);
			v[i*slices+j].x[2] = z;
			v[i*slices+j].x[3] = 1.;
			v[i*slices+j].c[0] = red;
			v[i*slices+j].c[1] = green;
			v[i*slices+j].c[2] = blue;
			v[i*slices+j].c[3] = 1.;
		}
	}

	GLuint *t = new GLuint[slices*stacks*6];
	int p = 0;
	for (int i=0; i<stacks; i++) {
		for (int j=0; j<slices; j++) {
			t[p++] = i*slices + j;
			t[p++] = i*slices + (j+1 == slices ? 0 : j+1);
			t[p++] = (i+1)*slices + j;
			t[p++] = i*slices + (j+1 == slices ? 0 : j+1);
			t[p++] = (i+1)*slices + (j+1 == slices ? 0 : j+1);
			t[p++] = (i+1)*slices + j;
		}
	}

	glGenBuffers(1, &vertex_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*slices*(stacks+1), v,
	             GL_STATIC_DRAW);

	glGenBuffers(1, &triangle_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*slices*stacks*6, t,
	             GL_STATIC_DRAW);

	delete[] v;
	delete[] t;
}

void Cone::draw() {
	//Inform OpenGL which handles to use
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	//Enable the arrays on the client side
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// number of coordinates per vertex (4 here),  coordinate value format,
	// stride between consecutive vertices, and pointers to the first coordinate
	glVertexPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, x)));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, c)));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Now we are ready to draw, using the triangle indices in the buffer
	glDrawElements(GL_TRIANGLES, slices*stacks*6, GL_UNSIGNED_INT,
	               reinterpret_cast<void*>(0));

	//Disable the arrays on the client side
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

Sphere::Sphere(float radius, int _m, int _n, float red, float green,
               float blue) {
	m=_m;
	n=_n;

	Vertex *vertices = new Vertex[(m+1)*(n+1)];
	for(int i=0; i<=m; i++)
	for(int j=0; j<=n; j++)
	{
		float theta = (i * 2 * M_PI)/m;
		float phi = (j * M_PI)/n - M_PI/2;
		vertices[i*(n+1)+j].x[0] = radius * cos(phi) * cos(theta);
		vertices[i*(n+1)+j].x[1] = radius * cos(phi) * sin(theta);
		vertices[i*(n+1)+j].x[2] = radius * sin(phi);
		vertices[i*(n+1)+j].x[3] = 1.;
		vertices[i*(n+1)+j].c[0] = red;
		vertices[i*(n+1)+j].c[1] = green;
		vertices[i*(n+1)+j].c[2] = blue;
		vertices[i*(n+1)+j].c[3] = 1.;
	}

	GLuint *triangles = new GLuint[m*n*6];
	int p=0;
	for(int i=0; i<m; i++)
	for(int j=0; j<n; j++)
	{
		triangles[p++]=(i  )*(n+1)+j;
		triangles[p++]=(i  )*(n+1)+j+1;
		triangles[p++]=(i+1)*(n+1)+j+1;
		triangles[p++]=(i  )*(n+1)+j;
		triangles[p++]=(i+1)*(n+1)+j+1;
		triangles[p++]=(i+1)*(n+1)+j;
	}

	glGenBuffers(1, &vertex_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*(m+1)*(n+1), vertices,
	             GL_STATIC_DRAW);

	//Create the triangle handle and copy the data to the GPU memory
	glGenBuffers(1, &triangle_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*m*n*6, triangles,
	             GL_STATIC_DRAW);

	delete[] vertices;
	delete[] triangles;
}

void Sphere::draw() {
	//Inform OpenGL which handles to use
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	//Enable the arrays on the client side
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// number of coordinates per vertex (4 here),  coordinate value format,
	// stride between consecutive vertices, and pointers to the first coordinate
	glVertexPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, x)));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, c)));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Now we are ready to draw, using the triangle indices in the buffer
	glDrawElements(GL_TRIANGLES, m*n*6, GL_UNSIGNED_INT,
	               reinterpret_cast<void*>(0));

	//Disable the arrays on the client side
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

SquarePlane::SquarePlane(float size, int _div, float red, float green,
                         float blue) {
	div = _div;

	Vertex *v = new Vertex[(div+1)*(div+1)];
	float divw = size/(float)div;
	float hsize = size/2.;
	for (int i=0; i<=div; i++) {
		for (int j=0; j<=div; j++) {
			int idx = i*(div+1)+j;
			v[idx].x[0] = j*divw - hsize;
			v[idx].x[1] = 0.;
			v[idx].x[2] = i*divw - hsize;
			v[idx].x[3] = 1.;
			v[idx].c[0] = red;
			v[idx].c[1] = green;
			v[idx].c[2] = blue;
			v[idx].c[3] = 1.;
		}
	}

	GLuint *t = new GLuint[div*div*6];
	int p = 0;
	for (int i=0; i<div; i++) {
		for (int j=0; j<div; j++) {
			t[p++] = i*(div+1)+j;
			t[p++] = i*(div+1)+j+1;
			t[p++] = (i+1)*(div+1)+j;
			t[p++] = i*(div+1)+j+1;
			t[p++] = (i+1)*(div+1)+j+1;
			t[p++] = (i+1)*(div+1)+j;
		}
	}

	glGenBuffers(1, &vertex_handle);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*(div+1)*(div+1), v,
	             GL_STATIC_DRAW);

	glGenBuffers(1, &triangle_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*div*div*6, t,
	             GL_STATIC_DRAW);

	delete[] v;
	delete[] t;
}

void SquarePlane::draw() {
	//Inform OpenGL which handles to use
	glBindBuffer(GL_ARRAY_BUFFER, vertex_handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangle_handle);
	//Enable the arrays on the client side
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// number of coordinates per vertex (4 here),  coordinate value format,
	// stride between consecutive vertices, and pointers to the first coordinate
	glVertexPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, x)));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex),
	                reinterpret_cast<void*>(offsetof(Vertex, c)));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Now we are ready to draw, using the triangle indices in the buffer
	glDrawElements(GL_TRIANGLES, div*div*6, GL_UNSIGNED_INT,
	               reinterpret_cast<void*>(0));

	//Disable the arrays on the client side
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

} // namespace lab2
