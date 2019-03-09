#ifndef MOVE
#define MOVE

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace move {
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 grav(glm::vec3 pos);
	const GLfloat getRotation();
	float jump();
	void resetV();
};
#endif