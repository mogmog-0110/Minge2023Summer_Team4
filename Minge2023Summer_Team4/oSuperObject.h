#pragma once
# include "Define.h"

class SuperObject
{
private:

protected:
	const Texture texture;
	// Array<Type> effectCommand
public:

	SuperObject();
	~SuperObject();

	virtual void update();
	virtual void draw(Vec2 offset) const;
};
