#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stack>
#include <SDL_image.h>
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include "Window.h"

using namespace std;

#pragma once
class AbstractDisplay {
public:
	virtual void display(SDL_Window* window) = 0;	//	used for drawing
	virtual void init() = 0;					//	initialiser

	GLuint meshObjects[3];						//	array of objects
	GLuint shaderProgram;						//	Phong Shader
	GLuint meshIndexCount = 0;
	stack<glm::mat4> mvStack;
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	glm::vec4 lightPos;


	rt3d::lightStruct light = {
	{0.3f, 0.3f, 0.3f, 1.0f}, // ambient
	{1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
	{1.0f, 1.0f, 1.0f, 1.0f}, // specular
	{-10.0f, 10.0f, 10.0f, 1.0f}  // position
	};

	rt3d::materialStruct material = {
		{0.4f, 0.4f, 1.0f, 1.0f}, // ambient
		{0.8f, 0.8f, 1.0f, 1.0f}, // diffuse
		{0.8f, 0.8f, 0.8f, 1.0f}, // specular
		1.0f  // shininess
	};

	//camera code
	glm::vec3 eye = glm::vec3(-15.0f, 2.0f, 0.0f);
	glm::vec3 at = glm::vec3(0.0f, 1.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};