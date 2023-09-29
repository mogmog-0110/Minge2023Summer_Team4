# pragma once
# include "../Define.h"
# include "../Figure.h"
# include "pObjectAppearanceManager.h"
# include "pEventManager.h"
# include "oPlayer.h"
# include "oDebris.h"
# include "oBullet.h"
# include "oEnemy.h"

class ObjectAppearanceManager;

class ObjectManager
{
private:


public:

	//各オブジェクトの配列
	Array<Debris*> myDebrises;
	Array<Bullet*> myBullets;
	Array<Enemy*> myEnemies;

	ObjectManager();
	~ObjectManager();

	Player* myPlayer;
	Debris testdebris{2000, 100, U"", Circle(50), {200,200}, {0,0},{0,0}};
	
	void update();
	void collision();
	void draw(Vec2 offset) const;

	void createEnemy();
	void createDebris();
};
