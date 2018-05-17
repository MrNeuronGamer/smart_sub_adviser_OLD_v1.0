#pragma once
#include "Manager.h"
#include "Data_Manager.h"

class Interaction_Manager :
	public Manager
{
private:
	Data_Manager Data;
	


public:
	Interaction_Manager(char* pPath);
	void launch();
	void get_command();
	void print_commands();

	~Interaction_Manager();
};

