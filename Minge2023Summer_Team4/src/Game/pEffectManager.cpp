#include "pEffectManager.h"

EffectManager* EffectManager::instance = nullptr;

EffectManager::EffectManager(const Vec2& offset_)
	:offset(offset_)
{
	
}

EffectManager::~EffectManager()
{
}

EffectManager* EffectManager::getInstance()
{
	return instance;
}

void EffectManager::create(const Vec2& offset_)
{
	if (instance == nullptr)
	{
		instance = new EffectManager(offset_);
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
