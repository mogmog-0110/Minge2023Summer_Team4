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


void EffectManager::create_damageScoreEffect(Vec2 pos, int32 score) {

	myEffect.add<damageScoreEffect>(pos, offset, score);
}



const void EffectManager::draw() {
	myEffect.update();
}
