#include "stdafx.h"

#include "AudioController.h"

CAudioController::CAudioController()
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Volume(-1, MIX_MAX_VOLUME);
}

CAudioController::~CAudioController()
{
	Mix_CloseAudio();
}

void CAudioController::PlayNoise(const CSound & audio)
{
	Mix_PlayChannel(-1, audio.GetSource(), 0);
}

void CAudioController::PlayMusic(const CMusic & music)
{
	Mix_PlayMusic(music.GetSource(), 0);
}

void CAudioController::StopNoise()
{
	Mix_HaltChannel(-1);
}

void CAudioController::StopMusic()
{
	Mix_HaltMusic();
}

void CAudioController::PauseNoise()
{
	Mix_Pause(-1);
}

void CAudioController::PauseMusic()
{
	Mix_PauseMusic();
}

void CAudioController::ResumeNoise()
{
	Mix_Resume(-1);
}

void CAudioController::ResumeMusic()
{
	Mix_ResumeMusic();
}

void CAudioController::RewindMusic()
{
	Mix_RewindMusic();
}

bool CAudioController::IsPlayingMusic() const
{
	return ((Mix_PlayingMusic()) ? (false) : (true));
}

/// volume is in 0..100
void CAudioController::SetNoiseVolume(const unsigned volume) // TODO: need to validate volume
{
	Mix_Volume(-1, MIX_MAX_VOLUME * volume / 100);
}

/// volume is in 0..100
void CAudioController::SetMusicVolume(const unsigned volume) // TODO: need to validate volume
{
	Mix_VolumeMusic(MIX_MAX_VOLUME * volume / 100);
}
