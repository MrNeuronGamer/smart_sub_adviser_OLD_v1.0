#pragma once
#include <string>
#include "Data_Manager.h"
#include <fstream>

class Subject
{
private:
	std::string Name;							/// Subject's name
	short unsigned int subj_key;				/// index of Subject inside of subjects pull
	short unsigned int Week_amount_theor;		/// Amount of theory which is supposed to do untill week ends
	short unsigned int Week_amount_pract;		/// Amount of practice which is supposed to do untill week ends
	short unsigned int Done_theor;				/// Amount of done theory for last day
	short unsigned int Done_pract;				/// Amount of done practice for last day
	short unsigned int Message_key;				/// Key of message to be shown
	short unsigned int Theory_priority;			/// Priority of theory
	short unsigned int Practice_priority;		/// Priority of practice
	short unsigned int time_spent_th;			/// Amount of spent time for studying theory last day 
	short unsigned int time_spent_pr;			/// Amount of spent time for doing practice last day 
	short unsigned int assigned_th;				/// Amount of theory to be assigned for last day				
	short unsigned int assigned_pr;				/// Amount of theory to be assigned for last day
	float time_coef;							/// Minutes per sub-amount
	short int days_after_lstus_th;				/// Day when the subject was used last time (theory sense)
	short int days_after_lstus_pr;				/// Day when the subject was used last time (practice sense)
	float prior_coef;							/// Standard multiplication coefficient for time
	bool Prac_flag;								/// Flag that shows if there is any practice for that subject


public:
	Subject(std::string name, float priority, bool prac_flag);
	void operator=(Subject A);
	friend std::ofstream& operator<< (std::ofstream& alt, class Subject Swaper);
	float prct_eff();
	float thry_eff();
	

	friend class Data_Manager;
	~Subject();
};

