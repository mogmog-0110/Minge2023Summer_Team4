# include "Define.h" // OpenSiv3D v0.6.11
#include "pGame.h"
#include "pTitle.h"
#include "pResult.h"

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// シーンマネージャーを作成
	App manager;

	// タイトルシーンを登録
	manager.add<Title>(SceneList::Title);
	manager.add<Game>(SceneList::Game);
	manager.add<Result>(SceneList::Result);

	manager.init(SceneList::Title);

	// 画面サイズを変更
	Window::Resize(1024, 768);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
