#include "Mesh.h"
#include <stdlib.h>
#include <sstream>
Mesh::Mesh(){}

Mesh::Mesh(vector<Vertex> &vertices_in, vector<GLuint> &indices_in)
{
	this->vertices = vertices_in;
	this->indices = indices_in;
	cout << "indices size:" << indices.size() << endl;
	setupMesh();
}

Mesh::Mesh(string FilePath)
{
	ifstream input_file(FilePath);
	const int LINE_LENGTH = 200;

	int vCount=0, vnCount = 0;

	while (input_file)
	{
		string type;
		input_file >> type;
		if (type.length() == 1)
		{
			switch (type[0]) {
			case '#': {
				char comment[LINE_LENGTH];
				input_file.getline(comment, LINE_LENGTH);
				printf("# %s\n", comment);
				break;
			}
			case 'v': {
				glm::vec3 vertCoord;
				input_file >> vertCoord[0] >> vertCoord[1] >> vertCoord[2];
				Vertex vert;
				vert.Position = vertCoord;
				this->vertices.push_back(vert);
				vCount++;
				break;
			}
			case 'f': {
				//int v_index[3];
				//int vn_index[3];
				string IndexPartStr;
				for (int i = 0; i < 3; i++) {
					input_file >> IndexPartStr;
					int splitIndex = IndexPartStr.find('/');
					istringstream temp(IndexPartStr.substr(0, splitIndex));
					int index;
					temp >> index;
					this->indices.push_back(index - 1);
				}
				break;
			}
			}
		}

		else if (type.length() == 2)
		{
			if (type == "vn") {
				glm::vec3 vertNormal;
				input_file >> vertNormal[0] >> vertNormal[1] >> vertNormal[2];
				this->vertices[vnCount].Normal = vertNormal;
				vnCount++;
				break;
			}
		}
	}
	
	input_file.close();
	cout << "vCount:" << vCount << "; vnCount:" << vnCount << endl;

	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Normal)));

	glBindVertexArray(0);
}

void Mesh::deleteBuffer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}