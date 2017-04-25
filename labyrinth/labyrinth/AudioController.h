#pragma once

#include "Audio.h"

// NOTE: more than a half of these methods were never called
// NOTE: do not use mp3, use wav for sounds & ogg for musics
// NOTE: do not use russian in paths
class CAudioController
{
public:
	CAudioController();
	~CAudioController();

	void PlaySound(const CSound & audio);
	void PlayMusic(const CMusic & audio);
	void StopSound();
	void StopMusic();
	void PauseSound();
	void PauseMusic();
	void ResumeSound();
	void ResumeMusic();

	void RewindMusic();

	bool IsPlayingMusic() const;

	void SetSoundVolume(const unsigned volume);
	void SetMusicVolume(const unsigned volume);

private:
};
