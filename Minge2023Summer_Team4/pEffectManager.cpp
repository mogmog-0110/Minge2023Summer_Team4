#include "stdafx.h"
#include "pEffectManager.h"

EffectManager* EffectManager::instance = nullptr;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

EffectManager* EffectManager::getInstance()
{
	return instance;
}

void EffectManager::create()
{
	if (instance == nullptr)
	{
		instance = new EffectManager();
	}
}

void EffectManager::destroy()
{
	delete instance;
	instance = nullptr;
}





const void EffectManager::draw() {
	myEffect.update();
}
