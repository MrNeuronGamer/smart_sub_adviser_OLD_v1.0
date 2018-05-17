#pragma once
#include <string>
#include "Data_Manager.h"


class Subject
{
private:
	std::string Name;
	short unsigned int subj_key;
	short unsigned int Week_amount_theor;
	short unsigned int Week_amount_pract;
	short unsigned int Done_theor;
	short unsigned int Done_pract;
	short unsigned int Message_key;
	short unsigned int Theory_priority;
	short unsigned int Practice_priority;
	short unsigned int time_spent;
	float time_coef; /// minutes per sub-amount
	short int days_after_lstus;
	float prior_coef;
	bool Prac_flag;


public:
	Subject(std::string name, float priority, bool prac_flag);

	friend class Data_Manager;
	~Subject();
};

