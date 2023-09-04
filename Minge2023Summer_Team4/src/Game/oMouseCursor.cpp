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
	this->texture.scaled(0.5).drawAt(Cursor::Pos());
}


