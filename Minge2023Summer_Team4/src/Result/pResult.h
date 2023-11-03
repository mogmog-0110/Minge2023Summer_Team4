#pragma once
#include"../Define.h"

class Result :public App::Scene {
private:

public:
	Result(const InitData& init);

	void update() override;
	void draw() const override;

	void debug();

	void iscleared();

};
