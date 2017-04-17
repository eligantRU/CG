#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include "Audio.h"

class CAudioController
{
public:
	CAudioController();
	~CAudioController();

	void Play(const CAudio & audio);
	void Stop();
	void Pause();
	void Resume();

	void SetVolume(const unsigned volume);

private:
};
