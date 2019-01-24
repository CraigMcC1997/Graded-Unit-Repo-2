#include "game.h"

// A simple cubemap loading function
GLuint game::loadCubeMap(const char *fname[6], GLuint *texID)
{
	glGenTextures(1, texID); // generate texture ID
	GLenum sides[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };
	SDL_Surface *tmpSurface;

	glBindTexture(GL_TEXTURE_CUBE_MAP, *texID); // bind texture and set parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	GLuint externalFormat;
	for (int i = 0; i < 6; i++)
	{
		// load file - using core SDL library
		tmpSurface = SDL_LoadBMP(fname[i]);
		if (!tmpSurface)
		{
			std::cout << "Error loading bitmap" << std::endl;
			return *texID;
		}

		// skybox textures should not have alpha (assuming this is true!)
		SDL_PixelFormat *format = tmpSurface->format;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;

		glTexImage2D(sides[i], 0, GL_RGB, tmpSurface->w, tmpSurface->h, 0,
			externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
		// texture loaded, free the temporary buffer
		SDL_FreeSurface(tmpSurface);
	}
	return *texID;	// return value of texure ID, redundant really
}

void game::init()
{
	//phong shader
	phongShaderProgram = rt3d::initShaders("../Shaders/phong-tex.vert", "../Shaders/phong-tex.frag");
	rt3d::setLight(phongShaderProgram, light0);
	rt3d::setMaterial(phongShaderProgram, material0);

	//skybox shader
	skyboxProgram = rt3d::initShaders("../Shaders/cubeMap.vert", "../Shaders/cubeMap.frag");

	//textures for skybox
	const char *cubeTexFiles[6] = {
		"../Resources/town-skybox/Town_ft.bmp", "../Resources/town-skybox/Town_bk.bmp",  "../Resources/town-skybox/Town_lf.bmp", "../Resources/town-skybox/Town_rt.bmp", "../Resources/town-skybox/Town2_up.bmp", "../Resources/town-skybox/Town_dn.bmp"
	};
	loadCubeMap(cubeTexFiles, &skybox[0]);

	lightPos = glm::vec4(-10.0f, 10.0f, 10.0f, 1.0f); //light position

	eye = glm::vec3(0.0f, 1.0f, 0.0f);
	at = glm::vec3(0.0f, 1.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	//Loading a cube object
	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	GLuint size = indices.size();
	meshIndexCount = size;
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), size, indices.data());

	//loading object
	verts.clear(); norms.clear(); tex_coords.clear(); indices.clear();
	rt3d::loadObj("../Resources/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount = indices.size();
	meshObjects[2] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), meshIndexCount, indices.data());
	/

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


// A simple texture loading function
GLuint game::loadTexture(const char *fname) {
	GLuint texID;
	glGenTextures(1, &texID); // generate texture ID

	// load file - using extended SDL_image library
	SDL_Surface * tmpSurface = IMG_Load(fname);

	if (!tmpSurface) {
		std::cout << "Error loading texture" << std::endl;
	}

	// bind texture and set parameters
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SDL_PixelFormat *format = tmpSurface->format;

	GLuint externalFormat, internalFormat;
	if (format->Amask) {
		internalFormat = GL_RGBA;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGBA : GL_BGRA;
	}
	else {
		internalFormat = GL_RGB;
		externalFormat = (format->Rmask < format->Bmask) ? GL_RGB : GL_BGR;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tmpSurface->w, tmpSurface->h, 0,
		externalFormat, GL_UNSIGNED_BYTE, tmpSurface->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(tmpSurface); // texture loaded, free the temporary buffer
	return texID;	// return value of texture ID
}


void game::update(SDL_Event _event)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) eye = move::moveRight(eye, move::getRotation(), 0.1f);
	if (keys[SDL_SCANCODE_S]) eye = move::moveRight(eye, move::getRotation(), -0.1f);
	if (keys[SDL_SCANCODE_SPACE]) eye = move::moveJump(eye);
	if (keys[SDL_SCANCODE_R]) eye.y += 0.1;
	if (keys[SDL_SCANCODE_F]) eye.y -= 0.1;

	//eye = move::grav(eye);

//	if (keys[SDL_SCANCODE_SPACE]) jumping = true;
		
	//if (jumping) {
	//	move::jump(eye.y);
	//}

	//float jump(float eye)
	//{
	//	while (velocity >= -10.0f)
	//	{
	//		eye += velocity;
	//		velocity += gravity;
	//		return eye;
	//	}
	//	//velocity = 0.5f;

	//}

	//std::cout << eye.x << ", " << eye.y << ", " << eye.z << std::endl;
}

void game::draw(SDL_Window* window)
{
	// clear the screen
	glEnable(GL_CULL_FACE);
	glClearColor(0.9f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection(1.0); // creating the projection matrix
	projection = glm::perspective(float(glm::radians(60.0f)), 800.0f / 600.0f, 1.0f, 150.0f); //setting up perspective
	rt3d::setUniformMatrix4fv(phongShaderProgram, "projection", glm::value_ptr(projection));
	GLfloat scale(1.0f); //used for scaling models & objects
	glm::mat4 modelview(1.0); // set base position for scene //creating the modelview matrix
	mvStack.push(modelview); // first push
	at = move::moveForward(eye, move::getRotation(), 1.0f); //what camera is looking at
	mvStack.top() = glm::lookAt(eye, at, up); //pushing camera to top of stack
	glUseProgram(skyboxProgram); // telling program what shader to use

	//skybox
	rt3d::setUniformMatrix4fv(skyboxProgram, "projection", glm::value_ptr(projection));
	glDepthMask(GL_FALSE); // make sure depth test is off
	glm::mat3 mvRotOnlyMat3 = glm::mat3(mvStack.top());
	mvStack.push(glm::mat4(mvRotOnlyMat3));

	glActiveTexture(GL_TEXTURE0);
	glCullFace(GL_FRONT); // drawing inside of cube!
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
	rt3d::setUniformMatrix4fv(skyboxProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();
	glCullFace(GL_BACK); // drawing inside of cube!

	// back to remainder of rendering
	glDepthMask(GL_TRUE); // make sure depth test is on

	glUseProgram(phongShaderProgram);

	//global light
	glm::vec4 tmp = mvStack.top()*lightPos;
	light0.position[0] = tmp.x;
	light0.position[1] = tmp.y;
	light0.position[2] = tmp.z;
	//std::cout << tmp.x << ", " << tmp.y << ", " << tmp.z << std::endl;
	rt3d::setLightPos(phongShaderProgram, glm::value_ptr(tmp));
	rt3d::setUniformMatrix4fv(phongShaderProgram, "projection", glm::value_ptr(projection));

	// draw a cube for ground plane
	glActiveTexture(GL_TEXTURE1); // < - 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->glu_tex_fabric);
	GLint tex1_uniform_loc = glGetUniformLocation(phongShaderProgram, "textureUnit0");
	glUniform1i(tex1_uniform_loc, 1);


	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-10.0f, -0.1f, -10.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(20.0f, 0.1f, 20.0f));
	rt3d::setUniformMatrix4fv(phongShaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(phongShaderProgram, material1);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();

	// draw object
	glUseProgram(phongShaderProgram);

	//enabling & binding textures which are passed to shader for blending
	glActiveTexture(GL_TEXTURE2); // < - 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->glu_tex_moss);
	tex1_uniform_loc = glGetUniformLocation(phongShaderProgram, "textureUnit0");
	glUniform1i(tex1_uniform_loc, 2);

	rt3d::setLightPos(phongShaderProgram, glm::value_ptr(tmp));
	rt3d::setUniformMatrix4fv(phongShaderProgram, "projection", glm::value_ptr(projection));
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(eye.x + 5.0f, eye.y, eye.z));	// moving object based on camera position
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale*0.5f, scale*0.5f, scale*0.5f));
	rt3d::setUniformMatrix4fv(phongShaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(phongShaderProgram, material1);
	rt3d::drawIndexedMesh(meshObjects[2], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();

	// remember to use at least one pop operation per push...
	mvStack.pop(); // initial matrix
	glDepthMask(GL_TRUE);
	SDL_GL_SwapWindow(window); // swap buffers
}