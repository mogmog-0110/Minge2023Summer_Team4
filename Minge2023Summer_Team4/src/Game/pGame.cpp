#include"pGame.h"

// 蓄積時間をグローバルで保持
double accumulatedTime = 0;

Game::Game(const InitData& init)
	: IScene(init), objectManager(), currentState(GameState::Loading), currentWave(0), accumulatedTime(0.0)
{
	Print << U"Game!";

	// 背景の色を設定 | Set background color
	Scene::SetBackground(Palette::Black);

	Print << U"Push [Q] key";

	myEffectManager = EffectManager::getInstance();

	// カメラの初期位置を設定
	cameraPos = Vec2(0, 0);
	topLeft = objectManager.myPlayer->getPos() - Scene::Center();

	// 敵データの読み込み
	objectManager.enemyDatas = objectManager.loadEnemyData(U"../src/Game/csvFile/enemy.csv");
	setUpBackground();
}


Game::~Game()
{
	
}



//====================================================
//毎Tick実行するかんすう

void Game::update()
{
	ClearPrint();
	switch (currentState)
	{
	case GameState::Loading:
		myPlayer = Player::getInstance();
		if (!waveLoaded && objectManager.myEnemies.empty()) {
			bool success = loadNextWave();
			if (!success) {
				currentState = GameState::Finished;
			}
			else {
				currentState = GameState::Playing;
				waveLoaded = true;
			}
		}
		break;

	case GameState::Playing:
		accumulatedTime += Scene::DeltaTime();
		if (KeyP.down()) {
			currentState = GameState::Pausing;
			break;
		}

		if (KeyQ.down()) {
			changeScene(SceneList::Result);
		}

		if (waveDataIndex < waveDatas.size()) {
			spawnEnemies();  // まだスポーンすべき敵が残っている場合は、敵をスポーンさせる
		}
		else if (objectManager.myEnemies.empty() && waveLoaded) {
			waveLoaded = false;  // 次のウェーブを読み込む準備
			currentState = GameState::Loading;
		}

		if (Player::getInstance()->isDead())
		{
			currentState = GameState::Dead;
		}

		scrollUpdate();
		objectManager.update();
		updateBackground();
		
		debug();
		break;

	case GameState::Pausing:
		if (KeyP.down()) {
			currentState = GameState::Playing;
		}
		break;

	case GameState::Dead:
		// キー入力を受け付けない
		// 敵の動きを止める
		objectManager.stopEnemies();
		// 死亡アニメーションを流す
		Player::getInstance()->playDeathAnimation();
		Scene::SetBackground(Palette::Black);
		if (Player::getInstance()->deathAnimationFinished()) {
			if (KeyEnter.down()) {
				changeScene(SceneList::Result); // アニメーション終了後にリザルトシーンへ遷移
			}
		}
		break;

	case GameState::Finished:
		changeScene(SceneList::Result);
	}
}


void Game::draw() const
{
	//従来のマウスカーソルを非表示に
	Cursor::RequestStyle(CursorStyle::Hidden);
	
	objectManager.draw(topLeft);
	myEffectManager->draw(topLeft);
	//TextureAsset(U"Frame").draw();
	miniMapDraw();
	cursor.draw();
	drawHpBar();
	drawMagicBook();

	// 文字
	dotFont1(U"HP").drawAt(896, 288, Color(255, 255, 255, 255));
	dotFont1(U"LEVEL ", Player::getInstance()->getLevel()).drawAt({896, 352}, Color(255, 255, 255, 255));
}

void Game::debug()
{

	Print << accumulatedTime;
	Print << U"レベル";
	Print << myPlayer->getInstance()->getLevel();
	Print << U"プレイヤーのステータス";
	Print << Player::getInstance()->getHp();

	Print << U"特殊弾";

	if (KeyEnter.down()) myEffectManager->create_spliteEffect(myPlayer->getPos(), U"Effect1", 0.25, 100);

	switch (objectManager.currentState)
	{
	case BulletType::SpecialA:
		Print << U"SpecialA";
		break;
	case BulletType::SpecialB:
		Print << U"SpecialB";
		break;
	case BulletType::SpecialC:
		Print << U"SpecialC";
		break;
	case BulletType::SpecialD:
		Print << U"SpecialD";
		break;
	case BulletType::None:
		Print << U"未取得";
		break;
	}
}

//====================================================
void Game::scrollUpdate()
{
	// カメラ座標をプレイヤーの座標に設定
	cameraPos = objectManager.myPlayer->getPos();
	topLeft = cameraPos - Scene::Center();

	// X軸のステージの内外判定
	if (FIELD_WIDTH > Scene::Width())
	{
		if (cameraPos.x - Scene::Center().x <= 0.0f)
		{
			cameraPos.x = Scene::Center().x;
		}
		else if (cameraPos.x + Scene::Center().x >= FIELD_WIDTH)
		{
			cameraPos.x = FIELD_WIDTH - Scene::Center().x;
		}
	}

	// Y軸のステージの内外判定
	if (FIELD_HEIGHT > Scene::Height())
	{
		if (cameraPos.y - Scene::Center().y <= 0.0f)
		{
			cameraPos.y = Scene::Center().y;
		}
		else if (cameraPos.y + Scene::Center().y >= FIELD_HEIGHT)
		{
			cameraPos.y = FIELD_HEIGHT - Scene::Center().y;
		}
	}

	cameraPos = convertToScreenPos(cameraPos);
	topLeft = convertToScreenPos(topLeft);
}


Vec2 Game::convertToScreenPos(Vec2 pos)
{
	return pos - (cameraPos - Scene::Center());
}



//====================================================
//ミニマップ関連のコード

void Game::miniMapDraw() const
{
	// マップの描写
	//Circle{ 896, 128, 128 }.draw(Palette::Gray);
	const Texture& mapFrame = TextureAsset(U"MiniMapFrame");
	mapFrame.drawAt(896, 128);

	//プレイヤーの描写
	Vec2 playerPos = objectManager.myPlayer->getPos() - topLeft;
	const Texture& playerIcon = TextureAsset(U"PlayerIcon");
	playerIcon.resized(20, 20).drawAt(896, 128);

	// 敵機の描写
	const Texture& enemyIcon = TextureAsset(U"EnemyIcon");
	Vec2 enemyPos;
	for (size_t i = 0; i < objectManager.myEnemies.size(); i++)
	{
		enemyPos = objectManager.myEnemies[i]->getPos() - topLeft;
		if (isInMiniMapRange(enemyPos))
		{
			double opacity = calculateOpacity(playerPos, enemyPos);
			ColorF color(1.0, opacity);  // 色を白（1.0, 1.0, 1.0）に設定し、透明度を設定
			enemyIcon.resized(16, 16).drawAt(calculateMiniMapPos(enemyPos), color);
		}

	}

	// デブリの描写
	const Texture& debriIcon = TextureAsset(U"DebriIcon");
	Vec2 debriPos;
	for (size_t i = 0; i < objectManager.myDebrises.size(); i++)
	{
		debriPos = objectManager.myDebrises[i]->getPos() - topLeft;
		if (isInMiniMapRange(debriPos))
		{
			double opacity = calculateOpacity(playerPos, debriPos);
			ColorF color(1.0, opacity);  // 色を白（1.0, 1.0, 1.0）に設定し、透明度を設定
			debriIcon.resized(16, 16).drawAt(calculateMiniMapPos(debriPos), color);
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
	const double maxDistance = 800;
	double opacity = 1.0 - (distance / maxDistance);
	return Clamp(opacity, 0.0, 1.0); // 透明度を0から1の範囲にクランプ
}

bool Game::loadNextWave()
{
	currentWave++;
	String fileName = Format(U"../src/Game/csvFile/wave", currentWave, U".csv");

	if (!FileSystem::Exists(fileName)) {
		return false;  // 次のウェーブのCSVファイルが存在しない
	}

	waveDatas.clear();  // 既存のwaveDatasをクリア
	waveDatas = objectManager.loadWaveData(fileName);
	waveDataIndex = 0;
	return true;
}

void Game::spawnEnemies()
{
	// ウェーブの敵がすべてスポーンしたかを確認
	if (waveDataIndex >= waveDatas.size()) {
		return;  // すべての敵がスポーンしたので、この関数から抜ける
	}

	if (accumulatedTime >= waveDatas[waveDataIndex].spawnTime) {
		for (int i = 0; i < waveDatas[waveDataIndex].spawnCount; ++i) {
			Enemy* enemy = objectManager.createEnemyFromData(waveDatas[waveDataIndex]);
			objectManager.myEnemies.push_back(enemy);
		}

		waveDataIndex++;

		accumulatedTime = 0.0; // accumulatedTimeリセット
	}
}

// 背景生成の処理に関する処理

void Game::setUpBackground() {
	// TextureAssetからテクスチャを直接取得
	const Texture& backgroundTexture = TextureAsset(U"Background");
	tileRegions = splitImage(backgroundTexture, 16 * EXPORT_SCALE, 16 * EXPORT_SCALE);

	// チャンクの数を計算
	int horizontalChunks = FIELD_WIDTH / (CHUNK_SIZE * TILE_SIZE) + 2; // +2 は余裕を持たせるため
	int verticalChunks = FIELD_HEIGHT / (CHUNK_SIZE * TILE_SIZE) + 2;

	// すべてのチャンクを生成
	for (int y = 0; y < verticalChunks; ++y) {
		for (int x = 0; x < horizontalChunks; ++x) {
			generateBackgroundChunk(Point(x, y));
		}
	}
}
void Game::updateBackground()
{
	// プレイヤーの位置を取得
	Vec2 playerPos = Player::getInstance()->getPos();

	// 描画するチャンクの範囲を計算 (拡張範囲を加える)
	int extendRange = 2;  // 拡張するチャンクの範囲
	RectF drawRect(playerPos.x - extendRange * CHUNK_SIZE * TILE_SIZE,
				   playerPos.y - extendRange * CHUNK_SIZE * TILE_SIZE,
				   Scene::Width() + 2 * extendRange * CHUNK_SIZE * TILE_SIZE,
				   Scene::Height() + 2 * extendRange * CHUNK_SIZE * TILE_SIZE);

	int startChunkX = static_cast<int>(drawRect.x / (CHUNK_SIZE * TILE_SIZE));
	int startChunkY = static_cast<int>(drawRect.y / (CHUNK_SIZE * TILE_SIZE));
	int endChunkX = static_cast<int>((drawRect.x + drawRect.w) / (CHUNK_SIZE * TILE_SIZE)) + 1;
	int endChunkY = static_cast<int>((drawRect.y + drawRect.h) / (CHUNK_SIZE * TILE_SIZE)) + 1;

	// 描画のオフセットを計算
	Vec2 offset = playerPos - Scene::Center();

	// 描画するチャンクをループ
	for (int chunkY = startChunkY; chunkY <= endChunkY; ++chunkY)
	{
		for (int chunkX = startChunkX; chunkX <= endChunkX; ++chunkX)
		{
			Point chunkPos(chunkX, chunkY);

			// 背景チャンクが生成されていない場合は生成
			if (!backgroundChunks.contains(chunkPos))
			{
				generateBackgroundChunk(chunkPos);
			}

			// チャンクを描画
			backgroundChunks[chunkPos].draw(tileRegions, offset);
		}
	}
}

// Perlinノイズ用の変数
PerlinNoise perlinNoise;


void Game::generateBackgroundChunk(Point chunkPos) {
	BackgroundChunk chunk;

	// PerlinNoise オブジェクトのインスタンス化
	PerlinNoise perlinNoise;

	for (int y = 0; y < CHUNK_SIZE; ++y) {
		for (int x = 0; x < CHUNK_SIZE; ++x) {
			BackgroundTile& tile = chunk.getTile(x, y);
			tile.pos = Vec2(chunkPos.x * CHUNK_SIZE * TILE_SIZE + x * TILE_SIZE,
							chunkPos.y * CHUNK_SIZE * TILE_SIZE + y * TILE_SIZE);

			// Perlin ノイズを使用して荒れ地を生成するかどうかを決定
			double offsetX = Random(7.0f);  // X軸方向のランダムなオフセット
			double offsetY = Random(7.0f);  // Y軸方向のランダムなオフセット
			double scale = 0.5f;  // スケールを調整（小さくすると大きなかたまりが生成される）
			double persistence = 0.3f;  // パーシスタンスを調整（小さい値で細かいテクスチャ）
			double threshold = Random(10.0f);  // 閾値を設定（大きい値で荒れ地がまばらになる）

			double noiseValue = perlinNoise.octave2D0_1((x + offsetX) * scale, (y + offsetY) * scale, 3, persistence);

			if (noiseValue > threshold) {
				tile.textureIndex = Random(9, 11);  // 9～11番目のテクスチャをランダムに選択
			}
			else {
				tile.textureIndex = Random(0, 8);  // 0～8番目のテクスチャをランダムに選択
			}
		}
	}

	backgroundChunks[chunkPos] = chunk;
}

void Game::drawMagicBook() const
{
	const Texture& mgFrame = TextureAsset(U"MagicFrame");
	const Texture& normalMagic = TextureAsset(U"NormalMagic");
	const Texture& laserMagic = TextureAsset(U"SpecialMagicA");
	const Texture& wideMagic = TextureAsset(U"SpecialMagicB");
	const Texture& pramaMagic = TextureAsset(U"SpecialMagicC");
	const Texture& mineMagic = TextureAsset(U"SpecialMagicD");

	Player* myPlayer = Player::getInstance();

	Array<Texture> bookTextures =
	{
		laserMagic,
		wideMagic,
		pramaMagic,
		mineMagic
	};

	Vec2 basePos = { 864, 400 };

	// フレームの描画位置
	Array<Vec2> bookPositions =
	{
		{928, 400},
		{832, 460},
		{896, 460},
		{960, 460}
	};

	// ノーマルブックのフレームとテクスチャを描画
	mgFrame.resized(64, 64).drawAt(basePos);
	normalMagic.resized(64, 64).drawAt(basePos);

	// 他の魔法書のフレームを描画
	for (int i = 0; i < bookPositions.size(); i++) {
		mgFrame.resized(64, 64).drawAt(bookPositions[i]);
	}

	// 取得している魔法書を描画、また選択している魔法書以外は半透明に。
	for (ItemType type : myPlayer->availableBullet)
	{
		int index = getBookTextureIndex(type);
		double alpha = 0.5;
    
		if (!(myPlayer->availableBullet.isEmpty()))
		{
			if (index == getBookTextureIndex(myPlayer->availableBullet[objectManager.currentIndex]))
			{
				alpha = 1;
			}
		}
		bookTextures[index].resized(64, 64).drawAt(bookPositions[index], ColorF(1, 1, 1, alpha));
	}

	// レベルの表示
	dotFont1(myPlayer->getBulletLevel(BulletType::Normal)).drawAt(basePos, Color(255, 255, 255, 255));
	dotFont1(myPlayer->getBulletLevel(BulletType::SpecialA)).drawAt(bookPositions[0], Color(255, 255, 255, 255));
	dotFont1(myPlayer->getBulletLevel(BulletType::SpecialB)).drawAt(bookPositions[1], Color(255, 255, 255, 255));
	dotFont1(myPlayer->getBulletLevel(BulletType::SpecialC)).drawAt(bookPositions[2], Color(255, 255, 255, 255));
	dotFont1(myPlayer->getBulletLevel(BulletType::SpecialD)).drawAt(bookPositions[3], Color(255, 255, 255, 255));
}



int Game::getBookTextureIndex(ItemType type) const
{
	switch (type) {
	case ItemType::SpecialMagicA: return 0;
	case ItemType::SpecialMagicB: return 1;
	case ItemType::SpecialMagicC: return 2;
	case ItemType::SpecialMagicD: return 3;
	default: return -1; // 無効な値
	}
}



void Game::drawHpBar() const
{
	Player* myPlayer = Player::getInstance();

	const Texture& hp = TextureAsset(U"Hp");
	const Texture& hpFrame = TextureAsset(U"HpFrame");

	// Hpバーの横幅の計算
	double gaugeWidth = (static_cast<double>(myPlayer->getHp()) / static_cast<double>(myPlayer->getMaxHp())) * hp.width() / 2;

	// HPバーの枠を描画
	hpFrame.resized(224, 32).drawAt(896, 320);

	// 描画するX座標の計算
	double startX = 896 - (hpFrame.width() / 2) + 112;

	// HPのゲージを描画（長さを変えて）
	hp.resized(gaugeWidth, 32).draw(startX, 320 - hp.height() / 2 + 16);
}



