#pragma once
#include"Define.h"
#include "oMouseCursor.h"

class Game :public App::Scene {
private:
	MouseCursor cursor;
public:
	Game(const InitData& init);
	~Game();

	void update() override;
	void draw() const override;

	void debug();

};
