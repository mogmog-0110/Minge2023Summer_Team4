#include"pTitle.h"

Title::Title(const InitData& init)
	:IScene(init)
{
	Print << U"Title!";

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.3, 0.2, 1.0 });

	// テキストを画面にデバッグ出力 | Print a text
	Print << U"Push [A] key";
}

void Title::update()
{

	if (KeyA.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Game);
	}

	debug();
}

void Title::draw() const
{
	TextureAsset(U"Title").draw();
}

void Title::debug()
{

}
