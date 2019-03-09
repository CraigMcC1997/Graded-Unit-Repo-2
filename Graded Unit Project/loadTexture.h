#pragma once

#ifndef LOADTEXTURE
#define LOADTEXTURE

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

namespace loadTexture {
	GLuint loadTextures(const char *fname);
};
#endif