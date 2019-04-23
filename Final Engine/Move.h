#pragma once

#ifndef MOVE
#define MOVE
#define DEG_TO_RADIAN 0.017453293
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

namespace Move
{
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveZ(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 grav(glm::vec3 pos);
	void setGrav(float);
	const GLfloat getRotation();
	glm::vec3 jump(glm::vec3);
	void resetV();
};
#endif