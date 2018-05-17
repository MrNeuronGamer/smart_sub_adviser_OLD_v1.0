#include "Subject.h"









Subject::Subject(std::string  name, float priority, bool prac_flag)
{
	Name = name;
	prior_coef = priority;
	Prac_flag = prac_flag;
	subj_key = 0;
	Week_amount_pract = 15;
	Week_amount_theor = 3;
	Done_pract = 0;
	Done_theor = 0;
	Message_key = 1;
	Theory_priority = 0;
	Practice_priority = 0;
	time_coef = 45;
	days_after_lstus = 0;
	
}



Subject::~Subject()
{
}
