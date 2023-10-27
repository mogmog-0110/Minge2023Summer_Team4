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

struct EnemyData {
	String name;
	int hp;
	int damage;
	String textureStr;
	Figure hitbox;
	double speed;
};

struct WaveData {
	double spawnTime;
	String enemyName;
	Vec2 spawnPos;
	double statusModifier; // 敵のステータスに掛けられる補正値
	int spawnCount;   
};

// ゲームの状態を表す
enum class GameState {
	Loading,
	Playing,
	Pausing,
	Dead,
	Finished
};


// アイテムの種類を表す
enum class ItemType {
	ExpPoint,
	NormalMagic,
	SpecialMagicA,
	SpecialMagicB,
	SpecialMagicC,
	SpecialMagicD,
};

// バレットの種類とステイトを表す
enum class BulletType {
	Normal,
	SpecialA,
	SpecialB,
	SpecialC,
	SpecialD,
	None, // 特殊弾を取得していない
};
