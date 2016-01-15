#include "FPSoundManager.h"
#include <climits>

void FPSoundManager::PlayStartGameBGM()
{
	m_startGameBGM = CreateZPlay();

	if (m_startGameBGM == nullptr) {
		m_startGameBGM->Release();
		return;
	}

	if (m_startGameBGM->OpenFile("../media/music/start_game.mp3", sfAutodetect) == 0) {
		m_startGameBGM->Release();
		return;
	}

	TStreamTime pCurrentTime;
	m_startGameBGM->GetPosition(&pCurrentTime);
	TStreamTime pEndTime;
	TStreamInfo pInfo;
	m_startGameBGM->GetStreamInfo(&pInfo);
	pEndTime.ms = pCurrentTime.ms + pInfo.Length.ms;
	if (m_startGameBGM->PlayLoop(tfMillisecond, &pCurrentTime, tfMillisecond, &pEndTime, INT_MAX, 1) == 0)
	{
		m_startGameBGM->Release(); // delete ZPlay class
		return;
	}
}

void FPSoundManager::StopStartGameBGM()
{
	m_startGameBGM->Stop();
	m_startGameBGM->Release();
}

void FPSoundManager::PlayPlayingGameBGM()
{
	m_playingGameBGM = CreateZPlay();

	if (m_playingGameBGM == nullptr) {
		m_playingGameBGM->Release();
		return;
	}

	if (m_playingGameBGM->OpenFile("../media/music/play_game.mp3", sfAutodetect) == 0) {
		m_playingGameBGM->Release();
		return;
	}

	TStreamTime pCurrentTime;
	m_playingGameBGM->GetPosition(&pCurrentTime);
	TStreamTime pEndTime;
	TStreamInfo pInfo;
	m_playingGameBGM->GetStreamInfo(&pInfo);
	pEndTime.ms = pCurrentTime.ms + pInfo.Length.ms;
	if (m_playingGameBGM->PlayLoop(tfMillisecond, &pCurrentTime, tfMillisecond, &pEndTime, INT_MAX, 1) == 0)
	{
		m_playingGameBGM->Release(); // delete ZPlay class
		return;
	}
}

void FPSoundManager::PlayMissileEmitSound()
{

}