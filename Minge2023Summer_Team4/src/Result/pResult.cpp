#include"pResult.h"

Result::Result(const InitData& init)
	:IScene(init)
{
	
	// 背景の色を設定 | Set background color
	Scene::SetBackground(Palette::Black);

}

void Result::update()
{

	if (MouseL.pressed())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Title);
	}

	debug();

}

void Result::draw() const
{
	Texture c = TextureAsset(U"clear1");
	Texture g = TextureAsset(U"gameOver");
	if (isCleared)
	{
		c.draw();
	}
	else
	{
		g.draw();
	}

}

void Result::debug()
{


}
