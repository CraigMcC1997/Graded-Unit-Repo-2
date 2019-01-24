#include "PlayerDisplay.h"


void PlayerDisplay::init()
{

	shaderProgram = rt3d::initShaders("../Shaders/phong.vert", "../Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light);
	rt3d::setMaterial(shaderProgram, material);

	lightPos = glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f);

	rt3d::loadObj("../Resources/MODEL.obj", verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObjects[1] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	textures[0] = loadTexture::loadTextures("../Resources/fabric.bmp");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PlayerDisplay::print(SDL_Window* window)
{
	glm::mat4 projection(1.0); // creating the projection matrix
	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	GLfloat scale(1.0f); //used for scaling models & objects
	glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
	mvStack.push(modelview); // first push
	at = move::moveForward(eye, move::getRotation(), 1.0f);
	mvStack.top() = glm::lookAt(eye, at, up); //pushing camera to top of stack

	glUseProgram(shaderProgram);

	glm::vec4 tmp = mvStack.top()*lightPos;
	light.position[0] = tmp.x;
	light.position[1] = tmp.y;
	light.position[2] = tmp.z;

	rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	// drawing player model
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(player->playerPos.x, player->playerPos.y, player->playerPos.z));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale*0.5f, scale*0.5f, scale*0.5f));
	mvStack.top() = glm::rotate(mvStack.top(), glm::radians(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	mvStack.top() = glm::rotate(mvStack.top(), -glm::radians(rotationValue), glm::vec3(0.0f, 1.0f, 0.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material);
	rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();

	// remember to use at least one pop operation per push...
	mvStack.pop(); // initial matrix
	glDepthMask(GL_TRUE);
	SDL_GL_SwapWindow(window); // swap buffers
}