#include"pTitle.h"

Title::Title(const InitData& init)
	:IScene(init)
{
	//Print << U"Title!";

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.3, 0.2, 1.0 });

	// テキストを画面にデバッグ出力 | Print a text
	//Print << U"Push [A] key";
}

void Title::update()
{

	if (MouseL.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Game);
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
