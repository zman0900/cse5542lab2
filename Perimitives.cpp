#include <cmath>

#include "Perimitives.h"

namespace lab2 {

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
		vertices[i*(n+1)+j].x[3] = 1;
		vertices[i*(n+1)+j].c[0] = red;
		vertices[i*(n+1)+j].c[1] = green;
		vertices[i*(n+1)+j].c[2] = blue;
		vertices[i*(n+1)+j].c[3] = 1;            
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
	glVertexPointer(4, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0); 
	glColorPointer (4, GL_FLOAT, sizeof(Vertex), (char*)NULL + 16); 

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Now we are ready to draw, using the triangle indices in the buffer 
	glDrawElements(GL_TRIANGLES, m*n*6, GL_UNSIGNED_INT, (char*)NULL + 0); 

	//Disable the arrays on the client side
	glDisableClientState(GL_VERTEX_ARRAY); 
	glDisableClientState(GL_COLOR_ARRAY);
}

} // namespace lab2
