#include "drawableEntity.h"

void DrawableEntity::init()
{
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light);
	rt3d::setMaterial(shaderProgram, material);
}

void DrawableEntity::update(SDL_Event _event)
{

}

void DrawableEntity::draw(SDL_Window* window)
{

}