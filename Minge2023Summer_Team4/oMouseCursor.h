#pragma once
# include "Define.h"
# include "pSuperObject.h"

class MouseCursor : public SuperObject
{
private:
	const Texture texture;
public:

	MouseCursor();
	~MouseCursor();
};
