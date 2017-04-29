#include "stdafx.h"

#include "AudioController.h"

CAudioController::CAudioController()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		throw std::runtime_error(Mix_GetError());
	}
	Mix_Volume(-1, MIX_MAX_VOLUME);
	Mix_AllocateChannels(16);
}

CAudioController::~CAudioController()
{
	Mix_CloseAudio();
}

void CAudioController::PlaySound(const CSound & audio)
{
	if (Mix_PlayChannel(-1, audio.GetSource(), 0) == -1)
	{
		throw std::runtime_error(Mix_GetError());
	}
}

void CAudioController::PlayMusic(const CMusic & music)
{
	if (Mix_PlayMusic(music.GetSource(), 0) == -1)
	{
		throw std::runtime_error(Mix_GetError());
	}
}

void CAudioController::StopSound()
{
	Mix_HaltChannel(-1);
}

void CAudioController::StopMusic()
{
	Mix_HaltMusic();
}

void CAudioController::PauseSound()
{
	Mix_Pause(-1);
}

void CAudioController::PauseMusic()
{
	Mix_PauseMusic();
}

void CAudioController::ResumeSound()
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

bool CAudioController::IsMusicPlaying() const
{
	return ((Mix_PlayingMusic()) ? (false) : (true));
}

bool CAudioController::IsMusicPaused() const
{
	return ((Mix_PausedMusic()) ? (false) : (true));
}

/// NOTE: never call SDL functions in callback
void CAudioController::HookMusicFinished(void(*callback)())
{
	Mix_HookMusicFinished(callback);
}

std::string CAudioController::GetError() const
{
	return {
		Mix_GetError()
	};
}

/// volume is in 0..100
void CAudioController::SetSoundVolume(const unsigned volume)
{
	if (!((0 <= volume) && (volume <= 100)))
	{
		throw std::invalid_argument("Volume must be in 0..100");
	}
	Mix_Volume(-1, MIX_MAX_VOLUME * volume / 100);
}

bool CAudioController::IsSoundsPaused() const
{
	return ((Mix_Paused(-1)) ? (false) : (true));
}

void CAudioController::HookSoundsFinished(void(*callback)(int channel))
{
	Mix_ChannelFinished(callback);
}

/// volume is in 0..100
void CAudioController::SetMusicVolume(const unsigned volume)
{
	if (!((0 <= volume) && (volume <= 100)))
	{
		throw std::invalid_argument("Volume must be in 0..100");
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME * volume / 100);
}
