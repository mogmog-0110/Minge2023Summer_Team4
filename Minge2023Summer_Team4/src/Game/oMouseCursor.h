#pragma once
#include "../Define.h"
#include "../oSuperObject.h"

class MouseCursor : public SuperObject
{
private:
	
public:
	MouseCursor();
	~MouseCursor();

	void draw() const;
};
