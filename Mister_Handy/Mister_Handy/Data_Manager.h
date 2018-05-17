#pragma once
#include "Manager.h"
#include <string>
#include <vector>
#include "Subject.h"


class Data_Manager :

	public Manager
{
private:

	std::vector<Subject> subj_pull;
	int Day;

public:
	Data_Manager();
	void create_new_subj(std::string name, float priority, bool prac_falg );


	~Data_Manager();
};

