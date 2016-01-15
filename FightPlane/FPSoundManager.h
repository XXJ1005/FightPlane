#pragma once

#include "libzplay.h"

using namespace libZPlay;

class FPSoundManager
{
public:
	FPSoundManager() {};
	~FPSoundManager();

	void PlayStartGameBGM(); // ��ʼ��Ϸ�����BGM
	void StopStartGameBGM();

	void PlayPlayingGameBGM(); // ������Ϸ�����BGM
	void StopPlayingGameBGM();

	void PlayMissileEmitSound(); // �������������
private:
	ZPlay *m_startGameBGM;
	ZPlay *m_playingGameBGM;
};