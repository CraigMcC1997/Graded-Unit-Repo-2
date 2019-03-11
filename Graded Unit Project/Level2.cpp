//#include "Level2.h"
//
//void Level2::init()
//{
//	//initialising shaders
//	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
//	rt3d::setLight(shaderProgram, light);
//	rt3d::setMaterial(shaderProgram, material);
//
//
//	//initialising positions
//	lightPos = glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f);
//	position[0] = glm::vec3(3.0f, 4.0f, -8.0f);
//	position[1] = glm::vec3(3.0f, 6.0f, -3.0f);
//	position[2] = glm::vec3(3.0f, 6.0f, 0.0f);
//	position[3] = glm::vec3(3.0f, 8.0f, 5.0f);
//
//	//initialising an object
//	verts.clear(); norms.clear(); tex_coords.clear(); indices.clear();
//	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
//	meshIndexCount = indices.size();
//	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), meshIndexCount, indices.data());
//
//	//loading textures
//	texture[0] = loadTexture::loadTextures("../Resources/fabric.bmp");
//	texture[1] = loadTexture::loadTextures("../Resources/moss.png");
//	texture[2] = loadTexture::loadTextures("../Resources/Jungle1.png");
//
//	sceneObjectName[0] = "../Resources/palmTree.obj";
//	sceneObjectName[1] = "../Resources/CrashBush.obj";
//
//	//initialising gl functions
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	//initialising player class
//	player->init();
//	//collectable->init();
//
//	////initialising the array of platforms
//	//for (int i = 0; i < MAX_PLATFORMS; i++)
//	//{
//	//	//platforms
//	//	_platform[i] = new platform(position[i]);
//	//	_platform[i]->init();
//	//	_platform[i]->Set_ShaderID(shaderProgram);
//	//}
//
////	for (int i = 0; i < MAX_OBJECTS; i++)
////	{
////		//Objects
////		object[i] = new drawObject();
////		object[i]->init(sceneObjectName[i]);
////		object[i]->Set_ShaderID(shaderProgram);
////	}
//}
//
//void Level2::update(SDL_Event _event)
//{
//	player->update(_event);
//	//collectable->update(_event);
//}
//
//void Level2::display(SDL_Window* window)
//{
//	// clear the screen
//	glEnable(GL_CULL_FACE);
//	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	
//	glm::mat4 projection(1.0); // creating the projection matrix
//	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective
//	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
//	
//	GLfloat scale(1.0f); //used for scaling models & objects
//	glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
//	
//	mvStack.push(modelview); // first push
//	//at = move::moveForward(eye, move::getRotation(), 1.0f);
//	//mvStack.top() = glm::lookAt(eye, at, up); //pushing camera to top of stack
//
//	glUseProgram(shaderProgram);	//setting up shader for use
//
//	//global light
//	glm::vec4 tmp = mvStack.top()*lightPos;
//	light.position[0] = tmp.x;
//	light.position[1] = tmp.y;
//	light.position[2] = tmp.z;
//	rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));
//	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
//
//	//ground plane
//	glBindTexture(GL_TEXTURE_2D, texture[1]);
//	mvStack.push(mvStack.top());
//	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(platformPos.x, platformPos.y, platformPos.z));
//	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(15.0f, 0.1f, 30.0f));
//	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
//	rt3d::setMaterial(shaderProgram, material);
//	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
//	mvStack.pop();
//
//	//back wall 1
//	glBindTexture(GL_TEXTURE_2D, texture[2]);
//	mvStack.push(mvStack.top());
//	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(10.0f, 8.0f, 0.0f));
//	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.5f, 20.0f, 35.0f));
//	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
//	rt3d::setMaterial(shaderProgram, material);
//	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
//	mvStack.pop();
//
//	////drawing the platforms
//	//for (int i = 0; i < MAX_PLATFORMS; i++)
//	//	_platform[i]->draw(&mvStack);
//	
//	//texture		//position					//scale							//stack
//	/*object[0]->draw(&textures[1], &glm::vec3(5.0f, 0.10f, 10.0f), &glm::vec3(0.01f, 0.01f, 0.01f), &mvStack);
//	object[1]->draw(&textures[1], &glm::vec3(0.0f, 0.10f, 0.0f), &glm::vec3(0.05f, 0.05f, 0.05f), &mvStack);*/
//
//	mvStack.pop();	//not sure if needed or not, not changes when removed
//
//	//collectable->draw(window);	//	drawing collectable
//	player->draw(window);	//	drawing player
//}