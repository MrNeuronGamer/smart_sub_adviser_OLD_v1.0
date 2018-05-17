#include "Data_Manager.h"



Data_Manager::Data_Manager()
{
}

void Data_Manager::create_new_subj(std::string name, float priority, bool prac_flag)
{
	Subject Alex(name, priority, prac_flag);
	Alex.subj_key = subj_pull.size() + 1;

	subj_pull.push_back(Alex);


}


Data_Manager::~Data_Manager()
{
}
