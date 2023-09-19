#include "pEventManager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}



void EventManager::debugCount() {
 	debugNum++;
}


// ゲームに呼び出されるデバッグコマンド。内容表示はこちらで
void EventManager::debug() {
	Print << debugNum;
}
