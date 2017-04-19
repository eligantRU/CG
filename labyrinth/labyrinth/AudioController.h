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

	void PlayNoise(const CSound & audio); // PlaySound() is fucking Microsoft API
	void PlayMusic(const CMusic & audio);
	void StopNoise();
	void StopMusic();
	void PauseNoise();
	void PauseMusic();
	void ResumeNoise();
	void ResumeMusic();

	void RewindMusic();

	bool IsPlayingMusic() const;

	void SetNoiseVolume(const unsigned volume);
	void SetMusicVolume(const unsigned volume);

private:
};
