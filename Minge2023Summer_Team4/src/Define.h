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

enum eObjectType {
	player,
	enemy,
	bullet,
	none,
	debris,
};



struct ObjectCreateCommand
{
	eObjectType occ_myType;
	int occ_hp;
	int occ_damage;
	String occ_textureStr;
	Figure occ_hitbox;
	Vec2 occ_pos;
	Vec2 occ_vel;
	Vec2 occ_acc;


	ObjectCreateCommand(eObjectType occ_myType_) :occ_myType(occ_myType_) {};
};
