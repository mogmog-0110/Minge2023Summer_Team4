#pragma once
#include "../Define.h"

struct dialogFormat
{
	String CharacterTexture;
	String CharacterName;
	String dialogString;

	// デフォルトコンストラクタを追加
	dialogFormat() = default;

	dialogFormat(const String& texture, const String& name, const String& dialog)
		: CharacterTexture(texture), CharacterName(name), dialogString(dialog) {}
};

struct TutorialFormat
{
	int tutoNumber;
	String videoName;
	String tutoText;
};


class GameScenario
{
private:

	// Videoの登録
	const VideoTexture video1{ U"Video/move.mp4", Loop::Yes };
	const VideoTexture video2{ U"Video/normalShot.mp4", Loop::Yes };
	const VideoTexture video3{ U"Video/specialShot1.mp4", Loop::Yes };
	const VideoTexture video4{ U"Video/specialShot2.mp4", Loop::Yes };
	const VideoTexture video5{ U"Video/regene.mp4", Loop::Yes };

	//Array<dialogFormat> scenario = { dialogFormat{U"", U"913", U"いけないなぁ…そういうのは"} };
	Array<String> dialogString = { U"あ",U"い" };

	Array<dialogFormat> scenario0 = {
		{U"Texture1.png", U"913", U"いけないなぁ…そういうのは"},
		{U"Texture2.png", U"913", U"俺の事を好きにならないやつは邪魔なんだよ"},
		{U"Texture3.png", U"913", U"真理は俺の母親になってくれるかもしれない女なんだ"}
	};

	Array<dialogFormat> scenario1 = {
		{U"Texture1.png", U"555", U"俺には夢がない。でもな、夢を守ることはできる"},
		{U"Texture2.png", U"555", U"戦うことが罪なら、俺が背負ってやる"}
	};

	Array<Array<dialogFormat>> scenario = { scenario0 ,scenario1 };

	Font dotFont = FontAsset(U"dotFont2");

	int selectedScenario = 1;
	int scenarioIndex = 0;

	TutorialFormat tuto1 =
	{
		1,U"move", U"WASDキーで移動できる"
	};

	TutorialFormat tuto2 =
	{
		2,U"normalShot", U"マウスを動かして敵の方向に照準を合わせる。\n左クリックで通常弾を発射する"
	};

	TutorialFormat tuto3 =
	{
		3,U"specialShot1", U"マウス右クリックで特殊弾を発射する。\n特殊弾は敵を倒したときに落とす魔法書を入手することで\n使用可能になる"
	};

	TutorialFormat tuto4 =
	{
		4,U"specialShot2", U"スペースキーかマウスのホイールクリックで\n特殊弾を選択できる。\n選択状態の特殊弾は画面右の魔法書でハイライト表示される"
	};

	TutorialFormat tuto5 =
	{
		5,U"regene", U"敵から攻撃を受けると画面右のHPが減少する。\n減少したHPは時間が経つと、自動回復する。\n立ち止まると回復効果が高まる"
	};

	TutorialFormat tuto6 =
	{
		6,U"", U"シイロ（416）はホムンクルスで、\n魔法使いの女の子。\n荒廃した聖皇国ログランで生まれ、\nその原因となった魔法実験の失敗が生んだ闇の軍勢と戦う。\n彼女の傍らで浮遊するのは相棒のクナ(97)。\n二人は世界の救世主となるべく旅を続けている"
	};

	Array<TutorialFormat> tutos =
	{
		tuto1, tuto2, tuto3, tuto4, tuto5, tuto6,
	};

public:
	GameScenario()
	{
	};

	bool update();
	void draw() const;
	void setScenario(int);
};

