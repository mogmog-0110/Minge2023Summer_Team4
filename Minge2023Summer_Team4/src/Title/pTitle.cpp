#include"pTitle.h"

Title::Title(const InitData& init)
	:IScene(init)
{
	//titleAudio.play();
	SoundPlayer::create();
	mySoundPlayer = SoundPlayer::getInstance();

	mySoundPlayer->playSound(eTitle,1s);
}


void Title::update()
{

	if (MouseL.down())
	{
		//タイトルシーンに遷移する
		mySoundPlayer->fadeoutAudio(1.5s);
		changeScene(SceneList::Game, 1s);
	}

	mySoundPlayer->update();

	debug();
}


void Title::draw() const
{
	Font dotFont = FontAsset(U"dotFont3");
	Font dotFont1 = FontAsset(U"dotFont1");

	TextureAsset(U"Title").draw();
	dotFont(U"Click to Start").drawAt( Scene::CenterF().x+150, Scene::Height() - 350 , Palette::Black);

	if (isCleared)
	{
		dotFont1(U"クリア特典").draw(100, Scene::Height() - 750, Palette::Black);
		dotFont1(U"無敵モード: \nPキーを押してから(ポーズ中に)J、K、Lキーを同時押し").draw(100, Scene::Height() - 700, Palette::Black);
		dotFont1(U"ヘルモード(超高難易度): \nPキーを押してから(ポーズ中に)H、Lキーを同時押し").draw(100, Scene::Height() - 650, Palette::Black);
	}
}


void Title::debug()
{

}
