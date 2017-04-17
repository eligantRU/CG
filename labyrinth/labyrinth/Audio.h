#pragma once

#include <string>

#include "AudioController.h"

class CAudioController;

class CAudio
{
	friend CAudioController;
public:
	CAudio() = delete;
	CAudio(const std::string & path)
		:m_sound(Mix_LoadWAV(path.c_str()))
	{

	}

	~CAudio()
	{
		Mix_FreeChunk(m_sound);
	}

private:
	Mix_Chunk * m_sound = nullptr;
};
