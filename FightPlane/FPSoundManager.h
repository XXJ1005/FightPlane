#pragma once

#include "libzplay.h"

using namespace libZPlay;

class FPSoundManager
{
public:
	FPSoundManager() {};
	~FPSoundManager();

	void PlayStartGameBGM(); // 开始游戏界面的BGM
	void StopStartGameBGM();

	void PlayPlayingGameBGM(); // 正在游戏界面的BGM
	void StopPlayingGameBGM();

	void PlayMissileEmitSound(); // 导弹发射的声音
	void PlayMissileBmobSound();  // 导弹击中敌方飞机的声音

	void PlayGamerHittedSound(); // 我方飞机被击中的声音
private:
	ZPlay *m_startGameBGM;
	ZPlay *m_playingGameBGM;
	ZPlay *m_playMissileEmitSound;
	ZPlay *m_playMissileBombSound;
	ZPlay *m_playGamerHittedSound;
};