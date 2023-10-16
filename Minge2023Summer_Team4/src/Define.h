#pragma once
# include <Siv3D.hpp> // OpenSiv3D v0.6.11
# include "Figure.h"

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

//　自分自身のオブジェクトタイプ
enum eObjectType {
	ePlayer,
	eEnemy,
	ePlayerBullet,
	eEnemyBullet,
	eDebris,
	eItem,
	eNone,
};
