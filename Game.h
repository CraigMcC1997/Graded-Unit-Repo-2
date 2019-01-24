#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stack>
#include <SDL_image.h>
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include "Move.h"

using namespace std;

class game
{
private:
	//shaders
	GLuint phongShaderProgram;
	GLuint skyboxProgram;
	GLuint skybox[5];


	//STUFF
	GLuint meshObjects[3];
	GLuint meshIndexCount = 0;
	stack<glm::mat4> mvStack;
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	glm::vec4 lightPos;
	bool jumping = false;
	float velocity = 10.0f;
	float gravity = -0.5f;

	float attConstant = 1.0f;
	float attLinear = 0.0f;
	float attQuadratic = 0.0f;


	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;

	rt3d::lightStruct light0 = {
	{0.3f, 0.3f, 0.3f, 1.0f}, // ambient
	{1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
	{1.0f, 1.0f, 1.0f, 1.0f}, // specular
	{-10.0f, 10.0f, 10.0f, 1.0f}  // position
	};

	rt3d::materialStruct material0 = {
		{0.2f, 0.4f, 0.2f, 1.0f}, // ambient
		{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
		{0.0f, 0.1f, 0.0f, 1.0f}, // specular
		2.0f  // shininess
	};
	rt3d::materialStruct material1 = {
		{0.4f, 0.4f, 1.0f, 1.0f}, // ambient
		{0.8f, 0.8f, 1.0f, 1.0f}, // diffuse
		{0.8f, 0.8f, 0.8f, 1.0f}, // specular
		1.0f  // shininess
	};

public:
	game() {}
	virtual ~game() {}
	void init();
	void update(SDL_Event _event);
	void draw(SDL_Window* window);
private:
	GLuint loadTexture(const char *fname);
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
};
