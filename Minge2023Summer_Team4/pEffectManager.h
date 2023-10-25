#pragma once
#include "src/Define.h"


class EffectManager
{
private:
	EffectManager();
	~EffectManager();

	EffectManager(const EffectManager&) = delete;
	EffectManager& operator=(const EffectManager&) = delete;

	// 唯一のインスタンスを格納する静的メンバー変数
	static EffectManager* instance;


	Effect myEffect;

public:

	// 唯一のインスタンスを取得するための静的メソッド
	static EffectManager* getInstance();

	// 唯一のインスタンスを作成
	static void create();

	// デストラクタ
	static void destroy();


	const void draw();
};
