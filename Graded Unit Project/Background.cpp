#include "Background.h"

void Background::init()
{
	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	texture = loadTexture::loadTextures("../Resources/Jungle1.png");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Background::Set_ShaderID(GLuint _id)
{
	shaderProgram = _id;
}

void Background::getStack(std::stack<glm::mat4>* stack)
{
	_mvStack = stack;
}

void Background::update(SDL_Event _event)
{

}

void Background::draw(SDL_Window* window)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	_mvStack->push(_mvStack->top());
	_mvStack->top() = glm::translate(_mvStack->top(), glm::vec3(10.0f, 8.0f, 0.0f));
	_mvStack->top() = glm::scale(_mvStack->top(), glm::vec3(0.5f, 20.0f, 35.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(_mvStack->top()));
	rt3d::setMaterial(shaderProgram, material);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	_mvStack->pop();
}
