﻿#include"pGame.h"

// 蓄積時間をグローバルで保持
double accumulatedTime = 0;

Game::Game(const InitData& init)
	: IScene(init), objectManager()
{
	Print << U"Game!";

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Print << U"Push [Q] key";

	topLeft = objectManager.myPlayer->getPos() - Scene::Center();

	objectManager.readEnemyCSV();
}


Game::~Game()
{

}



//====================================================
//毎Tick実行するかんすう

void Game::update()
{
	if (KeyQ.down())
	{
		//タイトルシーンに遷移する
		changeScene(SceneList::Result);
	}

	// 蓄積時間の計算
	accumulatedTime += Scene::DeltaTime();

	scrollUpdate();
	objectManager.update();
	objectManager.collision();

	startNextWave();
	Print << U"unti";
		
	debug();
}

void Game::draw() const
{

	//従来のマウスカーソルを非表示に
	Cursor::RequestStyle(CursorStyle::Hidden);

	//TextureAsset(U"Frame").draw();
	cursor.draw();
	objectManager.draw(topLeft);

	miniMapDraw();

	//仮フレーム
	//textureFrame.draw();

}

void Game::debug()
{
	ClearPrint();

	//マップスクロール用
	for (int32 i = 0; i < 100; ++i)
	{
		Circle{ -topLeft, (50 + i * 50) }.drawFrame(2);
	}

	Print << accumulatedTime;
	Print << currentWave; 

	for (size_t t = 0; t < 6; ++t)
	{
		
		Print << Waves[t][0];
		Print << Waves[t][1];
	}

	for (size_t t = 0; t < objectManager.enemyInfo.size(); ++t)
	{
		Print << objectManager.enemyInfo[t].enemyName;
		Print << objectManager.enemyInfo[t].hp;
		
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
	// マップの描写
	Circle{ 896, 128, 128 }.draw(Palette::Gray);

	//プレイヤーの描写
	Vec2 playerPos = objectManager.myPlayer->getPos() - topLeft;
	Circle{ calculateMiniMapPos(playerPos), 5 }.draw(Palette::Blue);

	// 敵機の描写
	Vec2 enemyPos;
	for (size_t i = 0; i < objectManager.myEnemies.size(); i++)
	{
		enemyPos = objectManager.myEnemies[i]->getPos() - topLeft;
		if (isInMiniMapRange(enemyPos))
		{
			Circle{ calculateMiniMapPos(enemyPos), 5 }.draw(ColorF(Palette::Red, calculateOpacity(playerPos, enemyPos)));
		}

	}

	// デブリの描写
	Vec2 debriPos;
	for (size_t i = 0; i < objectManager.myDebrises.size(); i++)
	{
		debriPos = objectManager.myDebrises[i]->getPos() - topLeft;
		if (isInMiniMapRange(debriPos))
		{
			Circle{ calculateMiniMapPos(debriPos), 5 }.draw(ColorF(Palette::Orange, calculateOpacity(playerPos, debriPos)));
		}

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

void Game::startNextWave()
{
	// waveを既に出現させているかを判定
	if (Waves[currentWave - 1][0] == false)
	{
		// waveファイルの選択→敵生成
		objectManager.readWaveCSV(currentWave);

		Waves[currentWave - 1][0] = true;
	}

	// waveがクリアしているかを判定
	if (Waves[currentWave - 1][1] == true)
	{
		currentWave++;
	}

	isWaveCleared();
}

void Game::isWaveCleared()
{
	// 体力ゼロの敵を追加。こうしないと出現判定の前に殲滅判定が動いてしまう。（消える処理より殲滅判定のほうがはやいかも）
	Enemy* newEnemy = ObjectAppearanceManager::createNewObject<Enemy>(eEnemy, 0, 10, U"", Rect(50), { -500,-500 }, { 0 , 0 }, { 1 , 1 });
	objectManager.myEnemies << newEnemy;

	if (objectManager.myEnemies.isEmpty())
	{
		Waves[currentWave - 1][1] = true;
	}
}
