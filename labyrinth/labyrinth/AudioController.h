#pragma once

#include "Audio.h"

// NOTE: more than a half of these methods were never called
// NOTE: do not use mp3, use wav for sounds & ogg for musics
// NOTE: only Latin in paths
// NOTE: think about translation paths to UTF8
class CAudioController
{
public:
	CAudioController(const CAudioController &) = delete;
	CAudioController & operator=(const CAudioController &) = delete;
	~CAudioController();

	static CAudioController & GetInstance();

	void PlaySound(const CSound & audio);
	void StopSound();
	void PauseSound();
	void ResumeSound();
	void SetSoundVolume(const unsigned volume);
	bool IsSoundsPaused() const;
	void HookSoundsFinished(void(*callback)(int channel));

	void PlayMusic(const CMusic & audio);
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();
	void RewindMusic();
	void SetMusicVolume(const unsigned volume);
	unsigned GetMusicVolume() const;
	bool IsMusicPlaying() const;
	bool IsMusicPaused() const;
	void HookMusicFinished(void(*callback)());

private:
	CAudioController();

	std::string GetError() const;
};
