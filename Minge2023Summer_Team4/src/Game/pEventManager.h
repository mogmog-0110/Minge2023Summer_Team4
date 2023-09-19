#pragma once
# include "../Define.h"



class EventManager
{
private:
	int debugNum = 0;
	
public:
	EventManager();
	~EventManager();

	void debugCount();
	void debug();
};
