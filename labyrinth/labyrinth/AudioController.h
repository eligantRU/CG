#pragma once

#include "Audio.h"

// NOTE: more than a half of these methods were never called
// NOTE: do not use mp3, use wav for sounds & ogg for musics
// NOTE: do not use russian in paths
// NOTE: think about translation path to UTF8
class CAudioController
{
public:
	CAudioController();
	~CAudioController();

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
	bool IsMusicPlaying() const;
	bool IsMusicPaused() const;
	void HookMusicFinished(void(*callback)());

private:
	std::string GetError() const;
};
