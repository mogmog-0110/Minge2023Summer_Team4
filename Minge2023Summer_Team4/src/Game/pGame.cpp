#include"pGame.h"

Game::Game(const InitData& init)
	:IScene(init), objectManager(ObjectManager{objectAppearanceManager})
{
	Print << U"Game!";
	
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Print << U"Push [Q] key";

	topLeft = objectManager.myPlayer->getPos() - Scene::Center();
}

Game::~Game()
{
}



void Game::update()
{

	if (KeyP.down()) objectAppearanceManager.debugCount();

	if (KeyQ.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Result);
	}

	scrollUpdate();
	objectManager.update();
	objectManager.collision();
	debug();

}

void Game::draw() const
{

	//従来のマウスカーソルを非表示に
	Cursor::RequestStyle(CursorStyle::Hidden);

	//objectManager.draw();
	//TextureAsset(U"Frame").draw();
	cursor.draw();
	objectManager.draw(topLeft);
}

void Game::debug()
{
	ClearPrint();
	objectAppearanceManager.debug();

	//マップスクロール用
	for (int32 i = 0; i < 100; ++i)
	{
		Circle{ -topLeft, (50 + i * 50) }.drawFrame(2);
	}
}

void Game::scrollUpdate()
{
	//カメラ座標と左上座標の更新
	cameraPos = objectManager.myPlayer->getPos();
	topLeft = cameraPos - Scene::Center();

	// X軸のステージの内外判定
	if (cameraPos.x - Scene::Center().x <= 0.0f)
	{
		cameraPos.x = Scene::Center().x;
	}
	else if (cameraPos.x + Scene::Center().x >= FIELD_WIDTH)
	{
		cameraPos.x = FIELD_WIDTH - Scene::Center().x;
	}

	// Y軸のステージの内外判定
	if (cameraPos.y - Scene::Center().y <= 0.0f)
	{
		cameraPos.y = Scene::Center().y;
	}
	else if (cameraPos.y + Scene::Center().y >= FIELD_HEIGHT)
	{
		cameraPos.y = FIELD_HEIGHT - Scene::Center().y;
	}

	cameraPos = convertToScreenPos(cameraPos);
	topLeft = convertToScreenPos(topLeft);

}

Vec2 Game::convertToScreenPos(Vec2 pos)
{

	// カメラ座標からスクリーン座標の原点に変換する
	Vec2 screenOriginPos = cameraPos - Scene::Center();

	// ワールド座標からスクリーン座標に変換する
	Vec2 screenPos = pos - screenOriginPos;

	return screenPos;
}

