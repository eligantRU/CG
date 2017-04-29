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
		if (m_source == nullptr)
		{
			throw std::runtime_error(Mix_GetError());
		}
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
	void SetVolume(const unsigned volume) 
	{
		if (!((0 <= volume) && (volume <= 100)))
		{
			throw std::invalid_argument("Volume must be in 0..100");
		}
		Mix_VolumeChunk(m_source, MIX_MAX_VOLUME * volume / 100);
	}

	unsigned GetVolume() const
	{
		return Mix_VolumeChunk(m_source, -1);
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
		if (m_source == nullptr)
		{
			throw std::runtime_error(Mix_GetError());
		}
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
