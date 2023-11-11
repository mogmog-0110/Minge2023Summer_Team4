﻿#include "pGameScenario.h"

bool GameScenario::update()
{
	if (KeySpace.down() || MouseL.down())
	{
		scenarioIndex++;
		if (scenario[selectedScenario].size() <= scenarioIndex) {
			scenarioIndex = 0;
			return true;
		}
		else return false;

	}
	else return false;
}

void GameScenario::draw() const
{
	/*Rect{ 60,525,900,200 }.drawFrame(3, 0, Palette::Red);
	Rect{ 80,485,150,40 }.drawFrame(3, 0, Palette::Red);

	dotFont(scenario[selectedScenario][scenarioIndex].CharacterName).draw(100, 490, Palette::White);
	dotFont(scenario[selectedScenario][scenarioIndex].dialogString).draw(80, 550, Palette::White);
	*/
	const Texture& image = TextureAsset(U"Tuto");
	image.draw(0, 0);
}

void GameScenario::setScenario(int selectedScenario_)
{
	selectedScenario = selectedScenario_;
}

