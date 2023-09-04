#pragma once
#include"../Define.h"
#include "../Figure.h"
#include "pObjectManager.h"
#include "oMouseCursor.h"

class Game :public App::Scene {
private:
	ObjectManager objectManager;
	MouseCursor cursor;

	Texture frameTex{ U"Image/frame.png" };
public:
	Game(const InitData& init);
	~Game();

	void update() override;
	void draw() const override;

	void debug();

};
