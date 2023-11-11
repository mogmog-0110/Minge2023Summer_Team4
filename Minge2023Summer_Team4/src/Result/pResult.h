#pragma once
#include "../Define.h"
#include "../pSoundPlayer.h"

class Result :public App::Scene {
private:
	SoundPlayer* mySoundPlayer;

	Array<String> tipString =
		{ U"特殊弾は右クリックで撃てるよ。\nスペースまたはマウスのホイールクリックで特殊弾を選べるよ",
		  U"それぞれの特殊弾にはいろんな特性があるよ。\n敵によって使い分けよう",
		  U"マインは超強力な特殊弾だよ。\nでもプレイヤーにも当たるから気をつけて",
		  U"キーボードのPキーを押すと、\nポーズができるよ",
		  U"シイロは主人公の女の子だよ。\n強力な魔法をたくさん使うことのできる魔法使いの女の子だよ",
		  U"クナはシイロの側で浮いている子供の幽霊だよ。\n二人はいつでも一緒",
	      U"ノーマル弾はレベルアップすると\n強力なホーミング弾に進化するよ" };

	String selectedTip;

	Font dotFont1 = FontAsset(U"dotFont1");
	Font dotTitle1 = FontAsset(U"dotTitle1");

public:
	Result(const InitData& init);

	void update() override;
	void draw() const override;

	void debug();


};
