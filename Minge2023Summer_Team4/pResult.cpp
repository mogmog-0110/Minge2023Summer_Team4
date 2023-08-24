#include"pResult.h"

Result::Result(const InitData& init)
	:IScene(init)
{
	Print << U"Result!";
	
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.1, 0.7, 1.0 });

	Print << U"Push [A] key";

}

void Result::update()
{

	if (KeyA.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Title);
	}

	debug();

}

void Result::draw() const
{
	
}

void Result::debug()
{


}
