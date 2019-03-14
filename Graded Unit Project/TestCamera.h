#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class testCamera
{
private:
	glm::vec3 eye = glm::vec3(-2.0f, 1.0f, 8.0f);
	glm::vec3 at = glm::vec3(0.0f, 1.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	glm::vec3 getEye()
	{
		return eye;
	}
	glm::vec3 getAt()
	{
		return at;
	}
	glm::vec3 getUp()
	{
		return up;
	}
	glm::vec3 setEye(glm::vec3 newEye)
	{
		eye = newEye;
		return eye;
	}
	glm::vec3 setAt(glm::vec3 newAt)
	{
		at = newAt;
		return at;
	}
	glm::vec3 setUp(glm::vec3 newUp)
	{
		up = newUp;
		return up;
	}

	glm::mat3 GetViewMatrix()
	{
		return glm::lookAt(eye, at, up);
	}
};