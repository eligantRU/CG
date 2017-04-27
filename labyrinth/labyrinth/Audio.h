#pragma once

#include <string>

// TODO: move to *.cpp
class IAudio
{
public:
	virtual ~IAudio() = default;
};

class CSound
	:public IAudio
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

private:
	Mix_Chunk * m_source = nullptr;
};

class CMusic
	:public IAudio
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
