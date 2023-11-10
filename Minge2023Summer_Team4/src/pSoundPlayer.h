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
	
public:

	// 唯一のインスタンスを取得するための静的メソッド
	static SoundPlayer* getInstance();

	// 唯一のインスタンスを作成
	static void create();

	// デストラクタ
	static void destroy();

	void playSound(enumSound eS);

	void fadeOutLoopAudio(Duration);


	void loopCheck();
};



