#pragma once
#include"../Define.h"
#include "../pSoundPlayer.h"

class Title :public App::Scene {
private:
	const Audio titleAudio{ Audio::Stream, U"Music/mapselect.mp3" };

	SoundPlayer* mySoundPlayer;

public:
	Title(const InitData& init);

	void update() override;
	void draw() const override;

	void debug();

};
