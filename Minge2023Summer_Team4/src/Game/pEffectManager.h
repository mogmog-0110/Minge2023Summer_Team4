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


	const void draw();
};


struct ScoreEffect : IEffect
{
	Vec2 m_pos;
	const Vec2& m_offset;

	int32 m_score;

	Font font{ FontMethod::MSDF, 20, Typeface::Bold };


	ScoreEffect(const Vec2& pos, const Vec2& offset, int32 score)
		: m_pos{ pos }
		, m_score{ score }
		, m_offset{ offset } {}

	bool update(double t) override
	{
		const HSV color{ (90 - m_score * 1.8), 1.0 - (t * 0.5) };

		font(m_score).drawAt((m_pos - m_offset).movedBy(0, t * -50), color);

		return (t < 0.5);
	}
};
