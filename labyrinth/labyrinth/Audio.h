#pragma once

#include <string>

// TODO: move to *.cpp

class CSound
{
public:
	CSound() = delete;
	CSound(const std::string & path)
		:m_source(Mix_LoadWAV(path.c_str()))
	{

	}

	~CSound()
	{
		Mix_FreeChunk(m_source);
	}

	Mix_Chunk * GetSource() const
	{
		return m_source;
	}

	/// volume is in 0..100
	void SetVolume(const unsigned volume) // TODO: need to validate volume
	{
		Mix_VolumeChunk(m_source, MIX_MAX_VOLUME * volume / 100);
	}

private:
	Mix_Chunk * m_source = nullptr;
};

class CMusic
{
public:
	CMusic() = delete;
	CMusic(const std::string & path)
		:m_source(Mix_LoadMUS(path.c_str()))
	{

	}

	~CMusic()
	{
		Mix_FreeMusic(m_source);
	}

	Mix_Music * GetSource() const
	{
		return m_source;
	}

private:
	Mix_Music * m_source = nullptr;
};
