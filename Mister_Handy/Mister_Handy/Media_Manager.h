#pragma once
#include "Manager.h"

class Media_Manager :
	public Manager
{
public:
	Media_Manager(char* pPath);
	void launch();
	~Media_Manager();
};

