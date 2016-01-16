#include "FPSoundManager.h"
#include <climits>

void FPSoundManager::PlayStartGameBGM()
{
	if (m_startGameBGM == nullptr){
		m_startGameBGM = CreateZPlay();
	}

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
	if (m_playingGameBGM == nullptr) {
		m_playingGameBGM = CreateZPlay();
	}

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
	if (m_playMissileEmitSound == nullptr) {
		m_playMissileEmitSound = CreateZPlay();
	}

	if (m_playMissileEmitSound == nullptr) {
		m_playMissileEmitSound->Release();
		return;
	}

	if (m_playMissileEmitSound->OpenFile("../media/music/missile_emit.wav", sfAutodetect) == 0) {
		m_playMissileEmitSound->Release();
		return;
	}

	TStreamTime pCurrentTime;
	m_playMissileEmitSound->GetPosition(&pCurrentTime);
	TStreamTime pEndTime;
	TStreamInfo pInfo;
	m_playMissileEmitSound->GetStreamInfo(&pInfo);
	pEndTime.ms = pCurrentTime.ms + pInfo.Length.ms;
	if (m_playMissileEmitSound->PlayLoop(tfMillisecond, &pCurrentTime, tfMillisecond, &pEndTime, INT_MAX, 1) == 0)
	{
		m_playMissileEmitSound->Release(); // delete ZPlay class
		return;
	}
}

void FPSoundManager::PlayMissileBmobSound()
{
	if (m_playMissileBombSound == nullptr){
		m_playMissileBombSound = CreateZPlay();
	}

	if (m_playMissileBombSound == nullptr) {
		m_playMissileBombSound->Release();
		return;
	}

	if (m_playMissileBombSound->OpenFile("../media/music/missile_bmob.wav", sfAutodetect) == 0) {
		m_playMissileBombSound->Release();
		return;
	}

	TStreamTime pCurrentTime;
	m_playMissileBombSound->GetPosition(&pCurrentTime);
	TStreamTime pEndTime;
	TStreamInfo pInfo;
	m_playMissileBombSound->GetStreamInfo(&pInfo);
	pEndTime.ms = pCurrentTime.ms + pInfo.Length.ms;
	if (m_playMissileBombSound->PlayLoop(tfMillisecond, &pCurrentTime, tfMillisecond, &pEndTime, INT_MAX, 1) == 0)
	{
		m_playMissileBombSound->Release(); // delete ZPlay class
		return;
	}
}

void FPSoundManager::PlayGamerHittedSound()
{
	if (m_playGamerHittedSound == nullptr) {
		m_playGamerHittedSound = CreateZPlay();
	}

	if (m_playGamerHittedSound == nullptr) {
		m_playGamerHittedSound->Release();
		return;
	}

	if (m_playGamerHittedSound->OpenFile("../media/music/gamer_hitted.wav", sfAutodetect) == 0) {
		m_playGamerHittedSound->Release();
		return;
	}

	TStreamTime pCurrentTime;
	m_playGamerHittedSound->GetPosition(&pCurrentTime);
	TStreamTime pEndTime;
	TStreamInfo pInfo;
	m_playGamerHittedSound->GetStreamInfo(&pInfo);
	pEndTime.ms = pCurrentTime.ms + pInfo.Length.ms;
	if (m_playGamerHittedSound->PlayLoop(tfMillisecond, &pCurrentTime, tfMillisecond, &pEndTime, INT_MAX, 1) == 0)
	{
		m_playGamerHittedSound->Release(); // delete ZPlay class
		return;
	}
}