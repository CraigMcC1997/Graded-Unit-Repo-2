#include "DrawObject.h"

void drawObject::init(const char* name)
{
	rt3d::loadObj(name, verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObject = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	material = {
	{ 0.4f, 0.2f, 0.2f, 1.0f }, // ambient
	{ 0.8f, 0.5f, 0.5f, 1.0f }, // diffuse
	{ 1.0f, 0.8f, 0.8f, 1.0f }, // specular
						2.0f	// shininess
	};
}

void drawObject::Set_ShaderID(GLuint _id)
{
	myShaderProgram = _id;
}

void drawObject::draw(GLuint *texture, glm::vec3 *position, glm::vec3 *scale, std::stack<glm::mat4> *_mvStack)
{
	//object
	glBindTexture(GL_TEXTURE_2D, *texture);
	_mvStack->push(_mvStack->top());
	_mvStack->top() = glm::translate(_mvStack->top(), *position);
	_mvStack->top() = glm::scale(_mvStack->top(), *scale);
	rt3d::setUniformMatrix4fv(myShaderProgram, "modelview", glm::value_ptr(_mvStack->top()));
	rt3d::setMaterial(myShaderProgram, material);
	rt3d::drawIndexedMesh(meshObject, meshIndexCount, GL_TRIANGLES);
	_mvStack->pop();
}
