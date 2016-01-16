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
	void PlayMissileBmobSound();  // �������ез��ɻ�������

	void PlayGamerHittedSound(); // �ҷ��ɻ������е�����
private:
	ZPlay *m_startGameBGM;
	ZPlay *m_playingGameBGM;
	ZPlay *m_playMissileEmitSound;
	ZPlay *m_playMissileBombSound;
	ZPlay *m_playGamerHittedSound;
};