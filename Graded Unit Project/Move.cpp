#include "Move.h"

using namespace std;

namespace move {

	//variables
	GLfloat r = 90.0f;
	float velocity = 1.0f;
	float gravity = -0.1f;

	// moving forwards & backwards
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d) {
		return glm::vec3(pos.x + d /** std::sin(glm::radians(r))*/, pos.y, pos.z /*- d * std::cos(glm::radians(r))*/);
	}

	// moving right & left
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d) {
		return glm::vec3(pos.x + d * std::cos(glm::radians(r)), pos.y, pos.z + d * std::sin(glm::radians(r)));
	}

	glm::vec3 grav(glm::vec3 pos) {
		return glm::vec3(pos.x, pos.y + gravity, pos.z);
	}

	float jump()
	{
		while (velocity >= -1.0f)
		{
			velocity += gravity;
			return velocity;
		}
		return velocity;
	}
	
	void resetV()
	{
		velocity = 1.0f;
	}

	const GLfloat getRotation()
	{
		return r;
	}
}