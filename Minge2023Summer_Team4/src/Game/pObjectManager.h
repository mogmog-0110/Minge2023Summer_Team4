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
	Timer DebugBulletTimer{ 0.2s, StartImmediately::Yes };

public:

	//各オブジェクトの配列
	Array<Debris*> myDebrises;
	Array<Bullet*> myPlayerBullets;
	Array<Bullet*> myEnemyBullets;
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
	void createBullet(bool, Vec2, Vec2, Vec2);
	void createBullet(ObjectInitData);
};
