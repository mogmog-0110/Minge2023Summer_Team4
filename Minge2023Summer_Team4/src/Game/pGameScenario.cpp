#include "pGameScenario.h"

bool GameScenario::update()
{
	if (KeySpace.down())
	{
		scenarioIndex++;
		if (scenario[selectedScenario].size() <= scenarioIndex) scenarioIndex = 0;
	}

	return true;
}

void GameScenario::draw() const
{
	Rect{ 60,525,900,200 }.drawFrame(3, 0, Palette::Red);
	Rect{ 80,485,150,40 }.drawFrame(3, 0, Palette::Red);

	dotFont(scenario[selectedScenario][scenarioIndex].CharacterName).draw(100, 490, Palette::Blue);
	dotFont(scenario[selectedScenario][scenarioIndex].dialogString).draw(80, 550, Palette::Blue);


	if (KeyPageDown.pressed())
	{
		Rect{ 70,500,150,25 }.drawFrame(3, 0, Palette::Red);
	}

}

void GameScenario::setScenario(int selectedScenario_)
{
	selectedScenario = selectedScenario_;
}

