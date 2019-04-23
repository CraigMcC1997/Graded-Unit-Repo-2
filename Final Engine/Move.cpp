#include "Move.h"

namespace Move
{
	//variables
	GLfloat r = 0.0f;
	float velocityY = 1.0f, velocityX = 0.125;
	float gravity = -0.05f;

	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d) {
		return glm::vec3(pos.x + d, pos.y, pos.z);
	}

	glm::vec3 moveZ(glm::vec3 pos, GLfloat angle, GLfloat d)
	{
		return glm::vec3(pos.x, pos.y, pos.z + d);
	}
	void setGrav(float newGrav)
	{
		gravity = newGrav;
	}

	glm::vec3 grav(glm::vec3 pos) {
		return glm::vec3(pos.x, pos.y + gravity, pos.z);
	}

	glm::vec3 jump(glm::vec3 position)
	{
		//while (velocityY >= -1.0f)
		//{
			position.y += velocityY;
			velocityY += gravity;
			return position;
		//}
		//return position;
	}

	void resetV()
	{
		velocityY = 1.0f;
	}

	const GLfloat getRotation()
	{
		return r;
	}
}