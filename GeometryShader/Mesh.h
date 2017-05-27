#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <GL\glew.h>
#include <glut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	vector<Vertex> vertices;
	vector<GLuint> indices;
	Mesh(vector<Vertex> &vertices_in, vector<GLuint> &indices_in);
	Mesh(string FilePath);
	GLuint VAO, VBO, EBO;
private:
	void setupMesh();
	void deleteBuffer();
};