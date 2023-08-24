#include"pGame.h"

Game::Game(const InitData& init)
	:IScene(init)
{
	Print << U"Game!";
	
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Print << U"Push [A] key";


}

void Game::update()
{

	if (KeyA.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Result);
	}

	debug();

}

void Game::draw() const
{
	
}

void Game::debug()
{


}
