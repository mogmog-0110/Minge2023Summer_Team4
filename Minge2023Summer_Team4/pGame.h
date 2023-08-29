#pragma once
#include"Define.h"
#include "pObjectManager.h"
#include "oMouseCursor.h"

class Game :public App::Scene {
private:
	ObjectManager objectManager;
	MouseCursor cursor;
public:
	Game(const InitData& init);
	~Game();

	void update() override;
	void draw() const override;

	void debug();

};
