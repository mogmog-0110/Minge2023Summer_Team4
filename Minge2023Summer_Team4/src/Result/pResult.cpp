#include"pResult.h"

Result::Result(const InitData& init)
	:IScene(init)
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(Palette::Black);
	mySoundPlayer = SoundPlayer::getInstance();
	mySoundPlayer->playSound(eGameOver, 0.5s);

	selectedTip = tipString.choice();
}

void Result::update()
{

	if (MouseL.pressed())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Title,2s);
		mySoundPlayer->fadeoutAudio(1s);
	}

	debug();

}

void Result::draw() const
{
	Texture c = TextureAsset(U"Clear");
	Texture g = TextureAsset(U"gameOver");
	if (isCleared)
	{
		dotTitle1(U"GAME").drawAt(500, 400, 100, ColorF(Palette::White));
		dotTitle1(U"CLEAR").drawAt(500, 600, 300, ColorF(Palette::White));
	}
	else
	{
		dotTitle1(U"GAME").drawAt(500, 400, 100, ColorF(Palette::White));
		dotTitle1(U"OVER").drawAt(500, 650, 300, ColorF(Palette::White));

		dotFont1(U"Tips").drawAt(25, 500, 575, ColorF(Palette::White));
		dotFont1(selectedTip).drawAt(25, 500, 650, ColorF(Palette::White));
	}
}

void Result::debug()
{


}
