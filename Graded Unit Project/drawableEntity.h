#pragma once
#include "Entity.h"

using namespace std;

class DrawableEntity : public Entity
{
protected:
	GLuint shaderProgram;						//	Phong Shader
	GLuint size;
	GLuint texture[5];
	GLuint meshObjects[3];
	GLuint meshIndexCount = 0;
	stack<glm::mat4> mvStack;
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	glm::vec4 lightPos;


public:
	virtual void update(SDL_Event _event) = 0;
	virtual void draw(SDL_Window* window) = 0;
};