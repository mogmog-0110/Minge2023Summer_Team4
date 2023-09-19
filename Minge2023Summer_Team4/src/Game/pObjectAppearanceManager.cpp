#include "pObjectAppearanceManager.h"

ObjectAppearanceManager::ObjectAppearanceManager()
{
}

ObjectAppearanceManager::~ObjectAppearanceManager()
{
}


void ObjectAppearanceManager::update()
{
	if (testTimer1.isRunning() == false)
	{
		BulletQueue.push_back(Bullet{ false, 1,200,U"",Circle(20),{0,200},{0,400},{0,0} });
		testTimer1.restart();
	}
}

void ObjectAppearanceManager::debug()
{

}

bool ObjectAppearanceManager::hasAnyQueue() {
	return !(BulletQueue.isEmpty() && DebrisQueue.isEmpty() && EnemyQueue.isEmpty());
}




void ObjectAppearanceManager::carryOutNewObject(
	Array<Debris>& myDebrises_, Array<Bullet>& myBullets_, Array<Enemy>& myEnemies_)
{
	/*
	myDebrises_.append(DebrisQueue);
	myBullets_.append(BulletQueue);
	myEnemies_.append(EnemyQueue);

	*/

	for (size_t i = 0; i < DebrisQueue.size(); i++)
	{
		myDebrises_.push_back(DebrisQueue[i]);
	}
	for (size_t i = 0; i < BulletQueue.size(); i++)
	{
		myBullets_.push_back(BulletQueue[i]);
	}
	for (size_t i = 0; i < EnemyQueue.size(); i++)
	{
		myEnemies_.push_back(EnemyQueue[i]);
	}

	Print << myDebrises_.size();

	DebrisQueue.clear();
	BulletQueue.clear();
	EnemyQueue.clear();
}



/*
void ObjectAppearanceManager::createNewObject(eObjectType myType_, int hp_, int damage_, String textureStr_,
	Figure hitbox_, Vec2 pos_, Vec2 vel_, Vec2 acc_)
{
	switch (myType_)
	{
	case player:
		break;
	case enemy:
		break;
	case bullet:
		break;
	case debris:
		objectDebrisQueue.push_back(Debris(this, hp_, damage_, textureStr_, hitbox_, pos_, acc_));
		break;
	default:
		break;
	}


}



// 初期デバッグ用
void ObjectAppearanceManager::debugCount() {
	debugNum++;
}


// ゲームに呼び出されるデバッグコマンド。内容表示はこちらで
void ObjectAppearanceManager::debug() {
	Print << debugNum;
}


*/

