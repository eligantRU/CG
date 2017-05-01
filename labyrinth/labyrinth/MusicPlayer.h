#pragma once

#include <string>
#include <vector>
#include <memory>

#include "AudioController.h"

class CMusicPlayer
{
public:
	CMusicPlayer() = delete;
	CMusicPlayer(const std::string & resPath);
	~CMusicPlayer() = default;

	void Update(float dt);

	void SetVolume(unsigned volume);
	void TurnUpVolume();
	void TurnDownVolume();
	unsigned GetVolume() const;

	void PlayPrevTrack();
	void PlayNextTrack();

	bool IsPlaying() const;
	bool IsPaused() const;

	void Play();
	void Stop();
	void Pause();
	void Resume();
	void Rewind();

private:
	std::vector<std::unique_ptr<CMusic>> m_trackList;
	unsigned m_volume = 5;

	bool m_isPause = false;
	bool m_isStoped = false;

	CAudioController & m_audioController;
};
