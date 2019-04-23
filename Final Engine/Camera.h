#pragma once
#ifndef CAMERA
#define CAMERA

//	#########################################
//	Camera used to track the player and 
//	allows the entire scene to be viewed as  
//	the camera moves
//	#########################################

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera
{
	glm::vec3 getEye();
	glm::vec3 getAt();
	glm::vec3 getUp();
	void setEye(glm::vec3 newEye);
	void setAt(glm::vec3 newAt);
	void setUp(glm::vec3 newUp);
};

#endif