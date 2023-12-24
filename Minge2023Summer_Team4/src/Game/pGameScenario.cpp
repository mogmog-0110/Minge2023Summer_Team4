#include "pGameScenario.h"

bool GameScenario::update()
{
	if (KeySpace.down() || MouseL.down())
	{
		scenarioIndex++;
		if (tutos.size() <= scenarioIndex) {
			scenarioIndex = 0;
			return true;
		}
		else return false;
	}
}

void GameScenario::draw() const
{
	const TutorialFormat& tuto = tutos[scenarioIndex];
	Rect{ 0,0,2000,2000 }.draw(ColorF(Palette::Black));

	// videoの再生
	switch (tuto.tutoNumber)
	{
	case 1:
		video1.scaled(0.5).drawAt(Scene::Center().x, Scene::Center().y - 100 );
		video1.advance();
		break;
	case 2:
		video2.scaled(0.5).drawAt(Scene::Center().x, Scene::Center().y - 100);
		video2.advance();
		break;
	case 3:
		video3.scaled(0.5).drawAt(Scene::Center().x, Scene::Center().y - 100);
		video3.advance();
		break;
	case 4:
		video4.scaled(0.5).drawAt(Scene::Center().x, Scene::Center().y - 100);
		video4.advance();
		break;
	case 5:
		video5.scaled(0.5).drawAt(Scene::Center().x, Scene::Center().y - 100);
		video5.advance();
		break;
	case 6:
		break;
	}

	if (tuto.tutoNumber != 6)
	{
		dotFont(tuto.tutoText).drawAt(500, 600, ColorF(Palette::White));
	}
	else
	{
		dotFont(tuto.tutoText).drawAt(Scene::Center(), ColorF(Palette::White));
	}
}

void GameScenario::setScenario(int selectedScenario_)
{
	selectedScenario = selectedScenario_;
}

