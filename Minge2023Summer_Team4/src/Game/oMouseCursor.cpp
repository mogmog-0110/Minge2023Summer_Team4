#include "oMouseCursor.h"

MouseCursor::MouseCursor()
{
}

MouseCursor::~MouseCursor()
{
}

void MouseCursor::draw() const
{
	// マウスカーソルを描画 | Draw mouse cursor
	TextureAsset(U"Cursor").scaled(0.5).drawAt(Cursor::Pos());
}


