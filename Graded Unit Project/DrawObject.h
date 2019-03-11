#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "loadTexture.h"
#include <stack>
#include <vector>

#include "Model.h"
#include "Camera.h"

using namespace std;

class drawObject 
{
private:
	GLuint myShaderProgram;
	GLuint meshObject;
	GLuint size;
	GLuint meshIndexCount = 0;

	Shader* shader;
	Model* myModel;
	Camera* camera;

public:
	drawObject() {};
	void init(const char* fileName);
	void draw(GLuint *texture, glm::vec3 *position, glm::vec3 *scale);
	//void Set_ShaderID(GLuint _id);
};