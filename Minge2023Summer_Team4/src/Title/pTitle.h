#pragma once
#include"../Define.h"

class Title :public App::Scene {
private:

public:
	Title(const InitData& init);

	void update() override;
	void draw() const override;

	void debug();

};
