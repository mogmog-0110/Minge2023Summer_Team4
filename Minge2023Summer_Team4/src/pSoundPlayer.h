#pragma once
#include "Define.h"

enum enumSound
{
	eTitle,
	eStageIntro,
	eStageLoop,
	eGameOver,
	eGameClear,
};

enum enumEffect
{
	effectShot,
	effectShotLaser,
	effectShotLaser2,
	effectShotWide,
	effectShotWide2,
	effectShotPrazma,
	effectShotMinePop,
	effectShotMineBoom,
	effectPickup,
	effectDead,
	effectHit1,
	effectHit2,
	effectHitPlayer,
	effectHitDebris,
};

class SoundPlayer
{
private:
	SoundPlayer();
	~SoundPlayer();

	SoundPlayer(const SoundPlayer&) = delete;
	SoundPlayer& operator=(const SoundPlayer&) = delete;

	// 唯一のインスタンスを格納する静的メンバー変数
	static SoundPlayer* instance;


	HashTable<enumSound, Audio> SoundTable;
	enumSound nowPlaying;

	HashTable<enumEffect, Audio> EffectTable;
	Array<Audio> arrEffect;
	int cnt = 0;
	bool isPlaying;

	void loopCheck();

public:

	// 唯一のインスタンスを取得するための静的メソッド
	static SoundPlayer* getInstance();

	// 唯一のインスタンスを作成
	static void create();

	// デストラクタ
	static void destroy();

	void playSound(enumSound eS, Duration fadeSecond);
	void playEffect(enumEffect eE);

	void fadeoutAudio(Duration);

	void update();

};



