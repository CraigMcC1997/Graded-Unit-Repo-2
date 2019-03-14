#include "Collectable.h"

void Collectable::init()
{
	collectablePos = glm::vec3(1.0f, 1.0f, 5.0f);

	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light);
	rt3d::setMaterial(shaderProgram, material);

	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObjects[1] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	texture[0] = loadTexture::loadTextures("../Resources/fabric.bmp");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Collectable::update(SDL_Event _event)
{

	// !!! NOT IN USE !!!

	//if (pDisplay->playerPos.x == cDisplay->collectablePos.x)
	//{
	//	if (pDisplay->playerPos.z == cDisplay->collectablePos.z)
	//	{
	//		cout << "collision" << endl;
	//		cDisplay->collectablePos.x = 20.0f;
	//	}
	//}

	// !!! NOT IN USE !!!
}

void Collectable::draw(SDL_Window* window)
{
	GLfloat scale(1.0f); //used for scaling models & objects
	glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
	mvStack.push(modelview); // first push
	mvStack.top() = glm::lookAt(eye, at, up); //pushing camera to top of stack

	glUseProgram(shaderProgram);

	//drawing object
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), collectablePos);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale*0.5f, scale*0.5f, scale*0.5f));
	mvStack.top() = glm::rotate(mvStack.top(), rotationValue, glm::vec3(0.0f, 1.0f, 0.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material);
	rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();
}