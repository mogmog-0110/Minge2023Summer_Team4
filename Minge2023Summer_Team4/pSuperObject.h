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

	void update();
	void draw(Vec2 offset) const;
};
