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


struct ScoreEffect : IEffect
{
	Vec2 m_pos;
	const Vec2& m_offset;

	int32 m_score;

	Font font{ FontMethod::MSDF, 48, Typeface::Heavy };


	ScoreEffect(const Vec2& pos, const Vec2& offset, int32 score)
		: m_pos{ pos }
		, m_score{ score }
		, m_offset{offset} {}

	bool update(double t) override
	{
		const HSV color{ (90 - m_score * 1.8), 1.0 - (t * 2.0) };

		font(m_score).drawAt(m_pos.movedBy(0, t * -120), color);

		return (t < 0.5);
	}
};
