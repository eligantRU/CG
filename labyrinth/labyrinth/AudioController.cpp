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

void CAudioController::Play(const CAudio & audio)
{
	Mix_PlayChannel(-1, audio.m_sound, 0);
}

void CAudioController::Stop()
{
	Mix_HaltChannel(-1);
}

void CAudioController::Pause()
{
	Mix_Pause(-1);
}

void CAudioController::Resume()
{
	Mix_Resume(-1);
}

/// volume is in 0..100
void CAudioController::SetVolume(const unsigned volume) // TODO: need to validate volume
{
	Mix_Volume(-1, volume * MIX_MAX_VOLUME);
}
