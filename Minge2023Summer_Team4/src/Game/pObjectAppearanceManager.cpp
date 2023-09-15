#include "pObjectAppearanceManager.h"

ObjectAppearanceManager::ObjectAppearanceManager()
{
}

ObjectAppearanceManager::~ObjectAppearanceManager()
{
}


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



void ObjectAppearanceManager::carryOutNewObject(Array<Debris>& myDebrises_) {
	myDebrises_.append(objectDebrisQueue);
}



// 初期デバッグ用
void ObjectAppearanceManager::debugCount() {
 	debugNum++;
}


// ゲームに呼び出されるデバッグコマンド。内容表示はこちらで
void ObjectAppearanceManager::debug() {
	Print << debugNum;
}
