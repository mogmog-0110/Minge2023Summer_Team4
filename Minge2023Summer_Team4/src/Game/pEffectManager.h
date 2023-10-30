﻿#pragma once
#include "../Define.h"


class EffectManager
{
private:
	EffectManager();
	~EffectManager();

	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;


	Array<TextureRegion> splitImage(const Texture& texture, int cellWidth, int cellHeight);

	// 唯一のインスタンスを格納する静的メンバー変数
	static EffectManager* instance;


	Effect myEffect;
	Vec2 offset; //drawするときの間接変数渡し（参照型）

public:

	// 唯一のインスタンスを取得するための静的メソッド
	static EffectManager* getInstance();

	// 唯一のインスタンスを作成
	static void create();

	// デストラクタ
	static void destroy();

	// エフェクト作成
	void create_damageScoreEffect(Vec2 pos, int32 score);

	// 描画
	const void draw(Vec2 offset);
};

//テスト用のダメージスコアエフェクト
struct damageScoreEffect : IEffect
{
	Vec2 m_pos;
	const Vec2& m_offset;

	int32 m_score;

	

	damageScoreEffect(const Vec2& pos, const Vec2& offset, int32 score)
		: m_pos{ pos }
		, m_score{ score }
		, m_offset{ offset } {}

	bool update(double t) override
	{
		
		FontAsset(U"dotFont1")(m_score).drawAt((m_pos - m_offset).movedBy(0, t * -75), Palette::Orange);
		
		return (t < 0.3);
	}
};
