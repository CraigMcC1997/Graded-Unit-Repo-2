#ifndef SOUND
#define SOUND
#ifndef NOMINMAX
#define NOMINMAX
#include <Windows.h>
#include <mmsystem.h>
#include "bass.h"
#include <GL/glew.h>

namespace Sound {
		//array of sound  files
	
	HSAMPLE loadSample(const char * filename);	//	load sound files
	void playSample(HSAMPLE sample);
};
#endif
#endif