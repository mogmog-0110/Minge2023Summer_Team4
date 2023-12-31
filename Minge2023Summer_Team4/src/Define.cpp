﻿# include "Define.h"

Array<TextureRegion> splitImage(const Texture& texture, int cellWidth, int cellHeight)
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

bool isCleared = false;
int defeatCount = 0;
int dropCount = 1;
int hellMode = 1;
bool muteki = false;
Vec2 closestEnemyPos = {-1, -1};
