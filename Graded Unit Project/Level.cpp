#include "Level.h"

void Level::init()
{
	//initialising shaders
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light);
	rt3d::setMaterial(shaderProgram, material);

	//initialising positions
	position[0] = glm::vec3(3.0f, 4.0f, -8.0f);
	position[1] = glm::vec3(3.0f, 6.0f, -3.0f);
	position[2] = glm::vec3(3.0f, 6.0f, 0.0f);
	position[3] = glm::vec3(3.0f, 8.0f, 5.0f);
	position[4] = glm::vec3(0.0f, -0.1f, 0.0f);

	scale[0] = glm::vec3(1.0f, 0.4f, 1.0f);
	scale[1] = glm::vec3(1.0f, 0.4f, 1.0f);
	scale[2] = glm::vec3(1.0f, 0.4f, 1.0f);
	scale[3] = glm::vec3(1.0f, 0.4f, 1.0f);
	scale[4] = glm::vec3(15.0f, 0.1f, 30.0f);

	//initialising an object
	verts.clear(); norms.clear(); tex_coords.clear(); indices.clear();
	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount = indices.size();
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), meshIndexCount, indices.data());


	//loading textures
	texture[0] = loadTexture::loadTextures("../Resources/fabric.bmp");
	texture[1] = loadTexture::loadTextures("../Resources/moss.png");
	

	name[0] = "../Resources/palmTree.obj";
	name[1] = "../Resources/CrashBush.obj";

	//initialising player class
	player->init();
	collectable->init();
	
	background->init();
	background->Set_ShaderID(shaderProgram);
	background->getStack(&mvStack);

	//initialising the array of platforms
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		//platforms
		_platform[i] = new platform(position[i], scale[i], texture[0]);
		_platform[i]->init();
		_platform[i]->Set_ShaderID(shaderProgram);
		_platform[i]->getStack(&mvStack);
	}

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		//Objects
		object[i] = new drawObject();
		object[i]->init(name[i]);
		object[i]->Set_ShaderID(shaderProgram);
	}

	//initialising gl functions
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Level::update(SDL_Event _event)
{
	player->update(_event);
	collectable->update(_event);

	//testing camera movements
	if (player->getPlayerPos().x >= 10.0f)
	{
		GLfloat PlayerX = player->getPlayerPos().x;
		GLfloat eyeY = camera.getEye().y;
		GLfloat eyeZ = camera.getEye().x;

		glm::vec3 camPos = glm::vec3(PlayerX, eyeY, eyeZ);

		camera.setEye(camPos);
	}
}

void Level::display(SDL_Window* window)
{
	// clear the screen
	glEnable(GL_CULL_FACE);
	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection(1.0); // creating the projection matrix
	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	GLfloat scale(1.0f); //used for scaling models & objects
	glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
	mvStack.push(modelview); // first push
	camera.setAt(move::moveForward(camera.getEye(), move::getRotation(), 1.0f));
	mvStack.top() = camera.GetViewMatrix(); //pushing camera to top of stack

	glUseProgram(shaderProgram);	//setting up shader for use

	//global light
	glm::vec4 tmp = mvStack.top()*lightPos;
	light.position[0] = tmp.x;
	light.position[1] = tmp.y;
	light.position[2] = tmp.z;
	rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	//back wall 1
	background->draw(window);

	//drawing the platforms
	for (int i = 0; i < MAX_PLATFORMS; i++)
		_platform[i]->draw(window);
	
	//texture		//position					//scale							//stack
	object[0]->draw(&texture[1], &glm::vec3(5.0f, 0.10f, 10.0f), &glm::vec3(0.01f, 0.01f, 0.01f), &mvStack);
	object[1]->draw(&texture[1], &glm::vec3(0.0f, 0.10f, 0.0f), &glm::vec3(0.05f, 0.05f, 0.05f), &mvStack);

	mvStack.pop();	//not sure if needed or not, not changes when removed

	collectable->draw(window);	//	drawing collectable
	player->draw(window);	//	drawing player
}