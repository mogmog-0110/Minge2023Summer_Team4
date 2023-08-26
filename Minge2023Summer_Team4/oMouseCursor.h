#pragma once
#include "Define.h"
#include "oSuperObject.h"

class MouseCursor : public SuperObject
{
private:
	const Texture texture{ U"../Image/Cursor.png" };
public:
	MouseCursor();
	~MouseCursor();

	void draw() const;
};
