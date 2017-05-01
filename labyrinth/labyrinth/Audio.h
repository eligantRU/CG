#pragma once

#include <string>

class CSound
{
public:
	CSound() = delete;
	CSound(const std::string & path);
	~CSound();

	void SetVolume(const unsigned volume);
	unsigned GetVolume() const;

	Mix_Chunk * GetSource() const;

private:
	Mix_Chunk * m_source = nullptr;
};

class CMusic
{
public:
	CMusic() = delete;
	CMusic(const std::string & path);

	~CMusic();

	Mix_Music * GetSource() const;

private:
	Mix_Music * m_source = nullptr;
};
