//	#########################################
//	A class used for loading in sound files
//	and playing sound effects
//	#########################################

#ifndef SOUND
#define SOUND
#ifndef NOMINMAX
#define NOMINMAX
#include "bass.h"
#include <Windows.h>
#include <mmsystem.h>
#include <GL/glew.h>

namespace Sound {
	//array of sound  files

	HSAMPLE loadSample(const char*, HSAMPLE);	//	load sound files
	void playSample(HSAMPLE sample);
};
#endif
#endif