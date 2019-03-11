#include "Collectable.h"

void Collectable::init()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, -3.0f));
	collectablePos = glm::vec3(4.0f, 0.0f, -18.0f);

	//shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	//rt3d::setLight(shaderProgram, light);
	//rt3d::setMaterial(shaderProgram, material);

	shader = new Shader("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");

	//lightPos = glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f);

	//eye = glm::vec3(0.0f, 1.0f, 0.0f);
	//at = glm::vec3(0.0f, 1.0f, -1.0f);
	//up = glm::vec3(0.0f, 1.0f, 0.0f);

	/*rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	size = indices.size();
	meshIndexCount = size;
	meshObjects[1] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());*/

	myModel = new Model("../Resources/cube.obj");

	//texture[0] = loadTexture::loadTextures("../Resources/fabric.bmp");

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
	glm::mat4 projection(1.0); // creating the projection matrix
	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective
	//rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	GLfloat scale(1.0f); //used for scaling models & objects
	//glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
	//mvStack.push(modelview); // first push
	//mvStack.top() = glm::lookAt(eye, at, up); //pushing camera to top of stack

	//glUseProgram(shaderProgram);

	shader->Use();

	//assimp stuf
	glm::mat4 view = camera->GetViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"),
		1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"),
		1, GL_FALSE, glm::value_ptr(view));

	glm::mat4x4 model;
	model = glm::translate(model, glm::vec3(collectablePos));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"),
		1, GL_FALSE, glm::value_ptr(model));
	myModel->Draw(*shader);

	//glm::vec4 tmp = mvStack.top()*lightPos;
	//light.position[0] = tmp.x;
	//light.position[1] = tmp.y;
	//light.position[2] = tmp.z;

	//rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));
	//rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	// drawing object
	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//mvStack.push(mvStack.top());
	//mvStack.top() = glm::translate(mvStack.top(), collectablePos);
	//mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale*0.5f, scale*0.5f, scale*0.5f));
	//mvStack.top() = glm::rotate(mvStack.top(), rotationValue, glm::vec3(0.0f, 1.0f, 0.0f));
	//rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	//rt3d::setMaterial(shaderProgram, material);
	//rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount, GL_TRIANGLES);
	//mvStack.pop();
}