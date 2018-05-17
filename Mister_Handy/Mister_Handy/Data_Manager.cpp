#include "Data_Manager.h"
#include <iostream>



Data_Manager::Data_Manager()
{
}

void Data_Manager::create_new_subj(std::string name, float priority, bool prac_flag)
{
	Subject Alex(name, priority, prac_flag);
	Alex.subj_key = subj_pull.size() + 1;

	subj_pull.push_back(Alex);


}

void Data_Manager::show_subjs()
{
	size_t Num = 1;
	for (Subject i : subj_pull)
	{
		std::cout << " " << Num++ << ".  " << i.Name << "\n";
		
	}

	std::cout << "\n";

}


Data_Manager::~Data_Manager()
{
}
