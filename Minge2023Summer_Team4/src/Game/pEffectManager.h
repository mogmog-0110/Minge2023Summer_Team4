#pragma once
#include "../Define.h"


class EffectManager
{
private:
	EffectManager(const Vec2& offset);
	~EffectManager();

	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;

	// 唯一のインスタンスを格納する静的メンバー変数
	static EffectManager* instance;


	Effect myEffect;
	const Vec2& offset;


public:

	// 唯一のインスタンスを取得するための静的メソッド
	static EffectManager* getInstance();

	// 唯一のインスタンスを作成
	static void create(const Vec2& offset);

	// デストラクタ
	static void destroy();

	// エフェクト作成
	void create_damageScoreEffect(Vec2 pos, int32 score);

	// 描画
	const void draw();
};


struct damageScoreEffect : IEffect
{
	Vec2 m_pos;
	const Vec2& m_offset;

	int32 m_score;

	Font font{ FontMethod::MSDF, 20, Typeface::Bold };


	damageScoreEffect(const Vec2& pos, const Vec2& offset, int32 score)
		: m_pos{ pos }
		, m_score{ score }
		, m_offset{ offset } {}

	bool update(double t) override
	{
		
		font(m_score).drawAt((m_pos - m_offset).movedBy(0, t * -20), Palette::Red);

		return (t < 0.5);
	}
};
