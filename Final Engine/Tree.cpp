#include "Tree.h"

void Tree::init()
{
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	rt3d::loadObj("../Resources/3D_Objects/palmTree.obj", verts, norms, tex_coords, indices);
	meshIndexCount[0] = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/PalmTex.png");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[0], indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Tree::update()
{
	//required to create entities
}

glm::vec3 Tree::getCollisionBox()
{
	return glm::vec3(NULL);
}

glm::vec3 Tree::getPosition()
{
	return glm::vec3(NULL);
}

void Tree::draw(SDL_Window* window)
{
	glm::mat4 modelview(1.0); // set base position for scene
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	stack<glm::mat4> mvStack;
	mvStack.push(modelview);

	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	glUseProgram(shaderProgram);

	for (GLfloat i = -70.0f; i < 290.0f; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		mvStack.push(mvStack.top());
		mvStack.top() = glm::translate(mvStack.top(), glm::vec3(15.0f, 1.0f, i));
		//mvStack.top() = glm::rotate(mvStack.top(), float(90.0f * DEG_TO_RADIAN), glm::vec3(0.0f, 1.0f, 0.0f));
		mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.075f, 0.075f, 0.075f));
		rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
		rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
		rt3d::setMaterial(shaderProgram, material1);
		rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount[0], GL_TRIANGLES);
		mvStack.pop();
		i += 10.0f;
	}

	mvStack.pop();
	glDepthMask(GL_TRUE);
}