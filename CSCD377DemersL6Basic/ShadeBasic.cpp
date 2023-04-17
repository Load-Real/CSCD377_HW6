#include "ShadeBasic.h"

unsigned int shade_vao;

void createShade()
{
	float side = 2.5f;
	const int numVertices = 12;

	//Type vec4
	vec4 shade_vertices[numVertices] = {
		// front triangle
		{0.0,  1.0, 0.0, 1.0f},      // P0
		{-side, 0.0, side, 1.0f},    // P1
		{side, 0.0, side, 1.0f},     // P2
		// right triangle
		{0.0,  1.0, 0.0, 1.0f},      // P0
		{side, 0.0, side, 1.0f},     // P2
		{side, 0.0, -side, 1.0f},    // P3
		// back triangle
		{0.0,  1.0, 0.0, 1.0f},      // P0
		{side, 0.0, -side, 1.0f},    // P3
		{-side, 0.0, -side, 1.0f},   // P4
		//left triangle
		{ 0.0,  1.0, 0.0, 1.0f},     // P0
		{-side, 0.0, -side, 1.0f},   // P4
		{ -side, 0.0, side, 1.0f},   // P1
	};

	//NormalF Computation
	vec3 P0 = vec3(shade_vertices[0]);
	vec3 P1 = vec3(shade_vertices[1]);
	vec3 P2 = vec3(shade_vertices[2]);

	vec3 normalF = normalize(cross(P1 - P0, P2 - P0));

	//NormalR Computation
	vec3 P3 = vec3(shade_vertices[5]);
	vec3 normalR = normalize(cross(P2 - P0, P3 - P0));

	//NormalB Computation
	vec3 P4 = vec3(shade_vertices[8]);
	vec3 normalB = normalize(cross(P4 - P0, P3 - P0));

	//NormalL Computation
	vec3 normalL = normalize(cross(P4 - P0, P1 - P0));

	//Type vec3
	vec3 shade_normals[numVertices] = {
			//Front Face
		    {normalF},
			{normalF},
			{normalF},

			//Right Face
			{normalR},
			{normalR},
			{normalR},

			//Back Face
			{normalB}, 
			{normalB},
			{normalB},

			//Left Face
			{normalL},
			{normalL},
			{normalL},
	};
	

	glGenVertexArrays(1, &shade_vao);
	glBindVertexArray(shade_vao);

	unsigned int handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shade_vertices), shade_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);  // Vertex position

	//Second param of glVertexAttribPointer is 3 because the normals are of type vec3 and not vec4
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shade_normals), shade_normals, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);  // Vertex normals

	glBindVertexArray(0);

}

void drawShade() {
	glBindVertexArray(shade_vao);
	glDrawArrays(GL_TRIANGLES,0, 12);
}