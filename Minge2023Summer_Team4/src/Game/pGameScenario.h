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


class GameScenario
{
private:
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

public:
	GameScenario()
	{
	};

	bool update();
	void draw() const;

	void setScenario(int);

};

