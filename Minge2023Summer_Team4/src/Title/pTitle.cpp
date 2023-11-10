#include"pTitle.h"

Title::Title(const InitData& init)
	:IScene(init)
{
	titleAudio.play();
}

void Title::update()
{

	if (MouseL.down())
	{
		//タイトルシーンに遷移する
		titleAudio.fadeVolume(0.0, 3s);
		changeScene(SceneList::Game, 3s);
	}

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
