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
	Finished
};

// ゲームの敵情報を格納する構造体
struct EnemyData{
	String enemyName;
	int hp;
	int damage;
	String textureName;
	Figure hitbox;
	double speed;
};

// ゲームのウェーブ情報を格納する構造体
struct WaveData {
	// int spawnTime;
	Vec2 spawnLocation;
	String enemyName;
	double statusMultiplier;
	int enemyCount;
};
