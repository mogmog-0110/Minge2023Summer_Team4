#include"pGame.h"

Game::Game(const InitData& init)
	:IScene(init)
{
	Print << U"Game!";
	
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	

	Print << U"Push [Q] key";

	MouseCursor cursor;
}

Game::~Game()
{
}



void Game::update()
{

	if (KeyQ.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Result);
	}

	objectManager.update();
	objectManager.collision();
	debug();

}

void Game::draw() const
{

	//従来のマウスカーソルを非表示に
	Cursor::RequestStyle(CursorStyle::Hidden);

	objectManager.draw();
	TextureAsset(U"Frame").draw();
	cursor.draw();
}

void Game::debug()
{


}
