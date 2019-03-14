#include "Platform.h"

void platform::init(void)
{
	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	material = {
	{ 0.4f, 0.2f, 0.2f, 1.0f }, // ambient
	{ 0.8f, 0.5f, 0.5f, 1.0f }, // diffuse
	{ 1.0f, 0.8f, 0.8f, 1.0f }, // specular
	2.0f // shininess
	};
}

void platform::Set_ShaderID(GLuint _id)
{
	shaderProgram = _id;
}

void platform::getStack(std::stack<glm::mat4>* stack)
{
	_mvStack = stack;
}

void platform::update(SDL_Event _event)
{
	//platforms dont move
}

void platform::draw(SDL_Window* window)
{
	//platform
	glBindTexture(GL_TEXTURE_2D, texture);
	_mvStack->push(_mvStack->top());
	_mvStack->top() = glm::translate(_mvStack->top(), position);
	_mvStack->top() = glm::scale(_mvStack->top(), scale);
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(_mvStack->top()));
	rt3d::setMaterial(shaderProgram, material);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	_mvStack->pop();
}
