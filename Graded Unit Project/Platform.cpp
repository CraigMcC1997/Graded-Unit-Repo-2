#include "Platform.h"

void platform::init(void)
{
	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObject = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	texture = loadTexture::loadTextures("../Resources/fabric.bmp");	//loading a texture

	material = {

	{ 0.4f, 0.2f, 0.2f, 1.0f }, // ambient

	{ 0.8f, 0.5f, 0.5f, 1.0f }, // diffuse

	{ 1.0f, 0.8f, 0.8f, 1.0f }, // specular

	2.0f // shininess
	};
}

void platform::Set_ShaderID(GLuint _id)
{
	myShaderProgram = _id;
}

glm::vec3 platform::getPosition()
{
	return position;
}

void platform::draw(std::stack<glm::mat4> *_mvStack)
{
	//platform
	glBindTexture(GL_TEXTURE_2D, texture);
	_mvStack->push(_mvStack->top());
	_mvStack->top() = glm::translate(_mvStack->top(), position);
	_mvStack->top() = glm::scale(_mvStack->top(), glm::vec3(1.0f, 0.4f, 1.0f));
	rt3d::setUniformMatrix4fv(myShaderProgram, "modelview", glm::value_ptr(_mvStack->top()));
	rt3d::setMaterial(myShaderProgram, material);
	rt3d::drawIndexedMesh(meshObject, meshIndexCount, GL_TRIANGLES);
	_mvStack->pop();
}
