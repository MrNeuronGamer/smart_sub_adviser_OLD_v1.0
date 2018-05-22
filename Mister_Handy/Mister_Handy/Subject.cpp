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
	days_after_lstus_th = 0;
	days_after_lstus_pr = 0;
	time_spent_th = 0;
	time_spent_pr = 0;
	assigned_pr = 0;
	assigned_th = 0;
}

void Subject::operator=(Subject A)
{
	Name = A.Name;
	subj_key = A.subj_key;
	Week_amount_theor = A.Week_amount_theor;
	Week_amount_pract = A.Week_amount_pract;
	Done_theor = A.Done_theor;
	Done_pract = A.Done_pract;
	Message_key = A.Message_key;
	Theory_priority = A.Theory_priority;
	Practice_priority = A.Practice_priority;
	time_spent_th = A.time_spent_th;
	time_spent_pr = A.time_spent_pr;
	time_coef = A.time_coef;
	days_after_lstus_th = A.days_after_lstus_th;
	days_after_lstus_pr = A.days_after_lstus_pr;
	prior_coef = A.prior_coef;
	Prac_flag = A.Prac_flag;
	assigned_pr = A.assigned_pr;
	assigned_th = A.assigned_th;

}

float Subject::prct_eff()
{
	float result = 0;

	result = Done_pract / (float)time_spent_pr*time_coef*7.0 / 10 + 3.0 / 10 * Done_pract / assigned_pr;

	return result;
}

float Subject::thry_eff()
{
	float result = 0;

	result = Done_theor / (float)time_spent_th*time_coef*7.0 / 10 + 3.0 / 10 * Done_theor / assigned_th;

	return result;
}



Subject::~Subject()
{
}

std::ofstream & operator << (std::ofstream & alt, Subject Swaper)
{
	
	alt << Swaper.Name << " ";
	alt << Swaper.Week_amount_theor << " ";
	alt << Swaper.Week_amount_pract << " ";
	alt << Swaper.Done_theor << " ";
	alt << Swaper.Done_pract << " ";
	alt << Swaper.Message_key << " ";
	alt << Swaper.Theory_priority << " ";
	alt << Swaper.Practice_priority << " ";
	alt << Swaper.time_spent_th << " ";
	alt << Swaper.time_spent_pr << " ";
	alt << Swaper.assigned_th << " ";
	alt << Swaper.assigned_pr << " ";
	alt << Swaper.time_coef << " ";
	alt << Swaper.days_after_lstus_th << " ";
	alt << Swaper.days_after_lstus_pr << " ";
	alt << Swaper.prior_coef << " ";
	alt << Swaper.Prac_flag << " ";

	return alt;
}
