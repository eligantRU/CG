#include "stdafx.h"

#include "MusicPlayer.h"

namespace
{

const std::string MUSIC_EXTENSION = ".ogg";

std::vector<std::string> FindFilesByExtension(const std::string & root, const std::string & extension)
{
	std::vector<std::string> result;
	for (boost::filesystem::directory_iterator it(root), end; it != end; ++it)
	{
		if (it->path().extension() == extension)
		{
			std::ostringstream stream;
			stream << *it;
			auto path = stream.str();
			result.push_back(path.substr(1, path.length() - 2));
		}
	}
	return result;
}

}

CMusicPlayer::CMusicPlayer(const std::string & resPath)
	:m_audioController(CAudioController::GetInstance())
{
	const auto trackPaths = FindFilesByExtension(resPath, MUSIC_EXTENSION);
	for (const auto & trackPath : trackPaths)
	{
		m_trackList.push_back(std::make_unique<CMusic>(trackPath));
	}
	SetVolume(m_volume);
	Play();
}

void CMusicPlayer::Update(float dt)
{
	(void)&dt;

	if (!m_audioController.IsMusicPlaying() && !m_isPause && !m_isStoped)
	{
		PlayNextTrack();
	}
}

/// volume is in 0..100
void CMusicPlayer::SetVolume(unsigned volume)
{
	if (!((0 <= volume) && (volume <= 100)))
	{
		throw std::invalid_argument("Volume must be in 0..100");
	}
	m_audioController.SetMusicVolume(volume);
}

void CMusicPlayer::TurnUpVolume()
{
	if ((0 <= m_volume) && (m_volume < 100))
	{
		SetVolume(++m_volume);
	}
}

void CMusicPlayer::TurnDownVolume()
{
	if ((0 < m_volume) && (m_volume <= 100))
	{
		SetVolume(--m_volume);
	}
}

unsigned CMusicPlayer::GetVolume() const
{
	return m_audioController.GetMusicVolume();
}

void CMusicPlayer::PlayPrevTrack()
{
	std::rotate(m_trackList.rbegin(), m_trackList.rbegin() + 1, m_trackList.rend());
	Play();
}

void CMusicPlayer::PlayNextTrack()
{
	std::rotate(m_trackList.begin(), m_trackList.begin() + 1, m_trackList.end());
	Play();
}

bool CMusicPlayer::IsPlaying() const
{
	return m_audioController.IsMusicPlaying();
}

bool CMusicPlayer::IsPaused() const
{
	return m_audioController.IsMusicPaused();
}

void CMusicPlayer::Play()
{
	m_audioController.PlayMusic(*m_trackList.front());
	m_isPause = false;
	m_isStoped = false;
}

void CMusicPlayer::Stop()
{
	m_audioController.StopMusic();
	m_isPause = false;
	m_isStoped = true;
}

void CMusicPlayer::Pause()
{
	m_audioController.PauseMusic();
	m_isPause = true;
	m_isStoped = false;
}

void CMusicPlayer::Resume()
{
	m_audioController.ResumeMusic();
	m_isPause = false;
	m_isStoped = false;
}

void CMusicPlayer::Rewind()
{
	m_audioController.RewindMusic();
	m_isPause = false;
	m_isStoped = false;
}
