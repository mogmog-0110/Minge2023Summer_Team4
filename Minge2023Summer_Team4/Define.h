#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.11

// シーンの名前
enum class SceneList {
	Title,
	Game,
	Result
};

// 共有するデータ
struct GameData
{
	int something;
};

using App = SceneManager<SceneList, GameData>;
