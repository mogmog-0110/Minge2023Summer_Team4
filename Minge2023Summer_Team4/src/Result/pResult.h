#pragma once
#include "../Define.h"
#include "../pSoundPlayer.h"

class Result :public App::Scene {
private:
	SoundPlayer* mySoundPlayer;

	Array<String> tipString =
		{ U"tip1",
		  U"tip2",
		  U"tip3",
		  U"tip4",
		  U"tip5",
		  U"tip6",
	      U"tip7" };

	Array<String> rdString = {
		U"A", U"B", U"C", U"D", U"E", U"F", U"G", U"H", U"I", U"J", U"K", U"U", U"M",
		U"N", U"O", U"P", U"Q", U"R", U"S", U"T", U"U", U"V", U"W", U"X", U"Y", U"Z"
	};
	String selectedTip;

	Font dotFont1 = FontAsset(U"dotFont1");
	Font dotTitle1 = FontAsset(U"dotTitle1");

public:
	Result(const InitData& init);

	void update() override;
	void draw() const override;

	void debug();


};
