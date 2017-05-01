#include "stdafx.h"

#include "Audio.h"

CSound::CSound(const std::string & path)
	:m_source(Mix_LoadWAV(path.c_str()))
{
	if (m_source == nullptr)
	{
		throw std::runtime_error(Mix_GetError());
	}
}

CSound::~CSound()
{
	Mix_FreeChunk(m_source);
}

Mix_Chunk * CSound::GetSource() const
{
	return m_source;
}

/// volume is in 0..100
void CSound::SetVolume(const unsigned volume)
{
	if (!((0 <= volume) && (volume <= 100)))
	{
		throw std::invalid_argument("Volume must be in 0..100");
	}
	Mix_VolumeChunk(m_source, MIX_MAX_VOLUME * volume / 100);
}

unsigned CSound::GetVolume() const
{
	return Mix_VolumeChunk(m_source, -1);
}

CMusic::CMusic(const std::string & path)
	:m_source(Mix_LoadMUS(path.c_str()))
{
	if (m_source == nullptr)
	{
		throw std::runtime_error(Mix_GetError());
	}
}

CMusic::~CMusic()
{
	Mix_FreeMusic(m_source);
}

Mix_Music * CMusic::GetSource() const
{
	return m_source;
}
