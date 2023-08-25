#pragma once
#include"Define.h"

class Game :public App::Scene {
private:
	MouseCursor mouseCursor;
public:
	Game(const InitData& init);

	void update() override;
	void draw() const override;

	void debug();

};
