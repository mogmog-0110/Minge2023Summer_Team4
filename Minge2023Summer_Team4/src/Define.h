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

enum eObjectType {
	player,
	enemy,
	bullet,
	none,
	debris,
};

/*

struct ObjectCreateCommand
{
	eObjectType occ_myType = eObjectType::none;
	int occ_hp = 1;
	int occ_damage = 1;
	String occ_textureStr = U"";
	Figure occ_hitbox;
	Vec2 occ_pos;
	Vec2 occ_vel;
	Vec2 occ_acc = { 0,0 };
};

*/
