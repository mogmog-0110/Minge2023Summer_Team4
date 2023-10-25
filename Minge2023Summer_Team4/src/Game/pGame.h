#pragma once
#include"../Define.h"
#include "../Figure.h"
#include "pObjectManager.h"
#include "oMouseCursor.h"
#include "pEffectManager.h"

class Player;

class Game :public App::Scene {
private:
	ObjectManager objectManager;
	MouseCursor cursor;
	Player* myPlayer;
	EffectManager* myEffectManager;

	//プレイヤーから見た相対的な左上座標
	Vec2 topLeft;

	//カメラ座標
	Vec2 cameraPos;

	//フィールドサイズ
	const int FIELD_WIDTH = 10000000000;
	const int FIELD_HEIGHT = 10000000000;

	// スクリーン画面の幅と高さ
	const Size screenSize{ 1024, 768 };

	// 実際のミニマップは256x256。
	const Size miniMapScaleSize = { 128, 128 };

	// 仮のフレーム素材
	const Texture textureFrame{ U"Image/frame_001.png" };

	GameState currentState;

	// 現在のウェーブ番号
	int currentWave;

	// 累積時間
	double accumulatedTime; 

	// 各ウェーブ情報を格納した配列
	Array<WaveData> waveDatas;

	// 上の配列にアクセスするための添字(インデックス)
	int waveDataIndex;

	// waveが読み込まれたどうか
	bool waveLoaded = false;


public:
	Game(const InitData& init);
	~Game();

	void update() override;
	void draw() const override;

	void debug();

	void scrollUpdate();
	Vec2 convertToScreenPos(Vec2 pos);

	void miniMapDraw() const;
	Vec2 calculateMiniMapPos(Vec2 pos) const;
	bool isInMiniMapRange(Vec2 pos) const;
	double calculateOpacity(Vec2 playerPos, Vec2 objectPos) const;

	bool loadNextWave();
	void spawnEnemies();

};
