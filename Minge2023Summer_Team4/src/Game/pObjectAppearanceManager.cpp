#include "pObjectAppearanceManager.h"

ObjectAppearanceManager::ObjectAppearanceManager()
{
}

ObjectAppearanceManager::~ObjectAppearanceManager()
{
}


// 初期デバッグ用
void ObjectAppearanceManager::debugCount() {
	debugNum++;
}


// ゲームに呼び出されるデバッグコマンド。内容表示はこちらで
void ObjectAppearanceManager::debug() {
	Print << debugNum;
}
