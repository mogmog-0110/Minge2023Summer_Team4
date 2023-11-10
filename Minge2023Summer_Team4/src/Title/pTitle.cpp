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
		changeScene(SceneList::Game, 3s);
	}

	mySoundPlayer->update();

	debug();
}




void Title::draw() const
{
	Font dotFont = FontAsset(U"dotFont3");

	TextureAsset(U"Title").draw();
	dotFont(U"Click to Start").drawAt( Scene::CenterF().x+150, Scene::Height() - 350 , Palette::Black);
}

void Title::debug()
{

}
