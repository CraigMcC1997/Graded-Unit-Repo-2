#include "Platform.h"

void platform::init(void)
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, -3.0f));
	shader = new Shader("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	myModel = new Model("../Resources/cube.obj");

	//rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	//size = indices.size();
	//meshIndexCount = size;
	//meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());


}

//void platform::Set_ShaderID(GLuint _id)
//{
//	shaderProgram = _id;
//}
//
//void platform::getStack(std::stack<glm::mat4>* stack)
//{
//	_mvStack = stack;
//}

void platform::update(SDL_Event _event)
{
	//platforms dont move
}

void platform::draw(SDL_Window* window)
{
	glm::mat4 projection(1.0); // creating the projection matrix
	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective

	shader->Use();

	//assimp stuf
	glm::mat4 view = camera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"),
		1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"),
		1, GL_FALSE, glm::value_ptr(view));

	glm::mat4x4 model;
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"),
		1, GL_FALSE, glm::value_ptr(model));
	myModel->Draw(*shader);

	//platform
	//glBindTexture(GL_TEXTURE_2D, texture);
	//_mvStack->push(_mvStack->top());
	//_mvStack->top() = glm::translate(_mvStack->top(), position);
	//_mvStack->top() = glm::scale(_mvStack->top(), scale);
	//rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(_mvStack->top()));
	//rt3d::setMaterial(shaderProgram, material);
	//rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	//_mvStack->pop();
}
