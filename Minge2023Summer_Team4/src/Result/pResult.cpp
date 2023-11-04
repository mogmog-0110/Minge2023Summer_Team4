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
	Texture c = TextureAsset(U"Clear");
	Texture g = TextureAsset(U"gameOver");
	if (isCleared)
	{
		c.draw(0,0);
	}
	else
	{
		g.draw(0, 0);
	}

}

void Result::debug()
{


}
