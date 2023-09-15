#pragma once
#include"../Define.h"
#include "../Figure.h"
#include "pObjectManager.h"
#include "oMouseCursor.h"

class Game :public App::Scene {
private:
	ObjectAppearanceManager objectAppearanceManager;
	ObjectManager objectManager;
	MouseCursor cursor;

	//プレイヤーから見た相対的な左上座標
	Vec2 topLeft;

	//カメラ座標
	Vec2 cameraPos;

	//フィールドサイズ
	const int FIELD_WIDTH = 10000000000;
	const int FIELD_HEIGHT =10000000000;

public:
	Game(const InitData& init);
	~Game();

	void update() override;
	void draw() const override;

	void debug();

	void scrollUpdate();
	Vec2 convertToScreenPos(Vec2 pos);
};
