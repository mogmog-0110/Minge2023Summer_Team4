#include"pTitle.h"

Title::Title(const InitData& init)
	:IScene(init)
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.3, 0.2, 1.0 });

	
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
