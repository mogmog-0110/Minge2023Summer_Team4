#include"pGame.h"

Game::Game(const InitData& init)
	: IScene(init), objectAppearanceManager(new ObjectAppearanceManager()), myEventManager(new EventManager()), objectManager(objectAppearanceManager, myEventManager)
{
	Print << U"Game!";

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Print << U"Push [Q] key";

	topLeft = objectManager.myPlayer->getPos() - Scene::Center();
}


Game::~Game()
{
	delete objectAppearanceManager;
	delete myEventManager;
}



//====================================================
//毎Tick実行するかんすう

void Game::update()
{

	if (KeyP.down()) myEventManager->debugCount();

	if (KeyQ.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Result);
	}

	scrollUpdate();
	objectManager.update();
	objectManager.collision();
		
	
	objectAppearanceManager->update();
	if (objectAppearanceManager->hasAnyQueue()) objectManager.getNewObject();
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

	miniMapDraw();

}

void Game::debug()
{
	//ClearPrint();
	//myEventManager->debug();

	//マップスクロール用
	for (int32 i = 0; i < 100; ++i)
	{
		Circle{ -topLeft, (50 + i * 50) }.drawFrame(2);
	}
}







//====================================================
//スクロール関係のコード。毎Tick実行する
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




//====================================================
//ミニマップ関連のコード

void Game::miniMapDraw() const
{
	//各オブジェクトのスクリーン座標の取得
	Vec2 playerPos = objectManager.myPlayer->getPos() - topLeft;
	Vec2 debriPos = objectManager.testdebris.getPos() - topLeft;

	//描画処理
	Rect{ 768, 0, 256, 256 }.draw(Palette::Gray);
	Circle{ calculateMiniMapPos(playerPos), 5 }.draw(Palette::Blue);

	if (isInMiniMapRange(debriPos))
	{
		Circle{ calculateMiniMapPos(debriPos), 5}.draw(ColorF(Palette::Red, calculateOpacity(playerPos, debriPos)));
	}
}

Vec2 Game::calculateMiniMapPos(Vec2 screenPos) const
{
	Vec2 miniMapPos;

	// スクリーン座標をミニ マップ座標に変換
	miniMapPos = (screenPos * miniMapScaleSize) / screenSize + Vec2{768 + 64 , 0 + 64};
	
	return miniMapPos;
}

bool Game::isInMiniMapRange(Vec2 pos) const
{
	Vec2 miniMapObjectPos = calculateMiniMapPos(pos);
	int adjVal = 3;

	return (miniMapObjectPos.x > 768 + adjVal && miniMapObjectPos.x < 1024 - adjVal && miniMapObjectPos.y > 0 + adjVal && miniMapObjectPos.y < 256 - adjVal);
}

double Game::calculateOpacity(Vec2 playerPos, Vec2 objectPos) const
{
	double distance = playerPos.distanceFrom(objectPos);
	const double maxDistance = 1024;
	double opacity = 1.0 - (distance / maxDistance);
	return Clamp(opacity, 0.0, 1.0); // 透明度を0から1の範囲にクランプ
}
