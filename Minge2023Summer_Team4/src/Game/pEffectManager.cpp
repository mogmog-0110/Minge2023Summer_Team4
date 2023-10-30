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


void EffectManager::create_damageScoreEffect(Vec2 pos, int32 score) {

	myEffect.add<damageScoreEffect>(pos, offset, score);
}



const void EffectManager::draw(Vec2 offset_) {
	offset = offset_;
	myEffect.update();
}


Array<TextureRegion> EffectManager::splitImage(const Texture& texture, int cellWidth, int cellHeight)
{
	Array<TextureRegion> regions;

	for (int y = 0; y < texture.height(); y += cellHeight)
	{
		for (int x = 0; x < texture.width(); x += cellWidth)
		{
			regions << texture(Rect(x, y, cellWidth, cellHeight));
		}
	}

	return regions;
}
