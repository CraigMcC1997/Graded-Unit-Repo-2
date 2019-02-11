#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "loadTexture.h"
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <stack>
#include <vector>

using namespace std;

class drawObject 
{
private:
	GLuint myShaderProgram;
	GLuint meshObject;
	GLuint size;
	GLuint meshIndexCount = 0;
	stack<glm::mat4> mvStack;
	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;
	rt3d::materialStruct material;

public:
	drawObject() {};
	void init(const char* name);
	void draw(GLuint *texture, glm::vec3 *position, glm::vec3 *scale, std::stack<glm::mat4> *_mvStack);
	void Set_ShaderID(GLuint _id);
};