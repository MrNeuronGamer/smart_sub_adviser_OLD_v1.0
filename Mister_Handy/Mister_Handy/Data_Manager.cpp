#include "Data_Manager.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>







void Data_Manager::refresh_times()
{
	for (Subject i : subj_pull)
	{
		i.days_after_lstus_pr++;
		i.days_after_lstus_th++;
	}

}

void Data_Manager::load_database()
{
	std::string buff(path);
	Subject Swaper(buff,1,1);
	int size_v = 0;

	std::ifstream IN;
	IN.open((buff + "\\database.dat").c_str());
	IN >> nt >> np >> current_day >> size_v;
	ch_sub_v.resize(size_v);

	for (int a = 0; a < size_v; a++)
	{
		IN >> ch_sub_v[a];

	}

	while (IN >> buff)
	{
		Swaper.Name = buff;
		IN >> Swaper.Week_amount_theor;
		IN >> Swaper.Week_amount_pract;
		IN >> Swaper.Done_theor;
		IN >> Swaper.Done_pract;
		IN >> Swaper.Message_key;
		IN >> Swaper.Theory_priority;
		IN >> Swaper.Practice_priority;
		IN >> Swaper.time_spent_th;
		IN >> Swaper.time_spent_pr;
		IN >> Swaper.assigned_th;
		IN >> Swaper.assigned_pr;
		IN >> Swaper.time_coef;
		IN >> Swaper.days_after_lstus_th;
		IN >> Swaper.days_after_lstus_pr;
		IN >> Swaper.prior_coef;
		IN >> Swaper.Prac_flag;

		Swaper.subj_key = subj_pull.size() + 1;
		subj_pull.push_back(Swaper);
		

	}

	IN.close();

}

void Data_Manager::form_day_pull()
{
	short int used_s = 0;
	bool first = true;
	int target = 0;

	for (int a = 0; a < nt; a++)
	{
		first = true;
		if (used_s == subj_pull.size()) break;

		for (Subject i : subj_pull)
		{

			if (std::find(std::begin(ch_sub_v), std::end(ch_sub_v), i.subj_key - 1) != std::end(ch_sub_v)) continue;

			if (first)
			{
				target = i.subj_key - 1;
				first = false;
				continue;

			}

			if (subj_pull[target].Theory_priority < i.Theory_priority) target = i.subj_key - 1;



		}

		ch_sub_v.push_back(target);
		used_s++;

	}

	used_s = 0;

	for (int a = nt; a <np + nt; a++)
	{
		first = true;
		if (used_s == subj_pull.size()) break;

		for (Subject i : subj_pull)
		{

			if (std::find(std::begin(ch_sub_v) + nt, std::end(ch_sub_v), i.subj_key - 1) != std::end(ch_sub_v)) continue;

			if (first)
			{
				target = i.subj_key - 1;
				first = false;
				continue;

			}

			if (subj_pull[target].Practice_priority< i.Practice_priority) target = i.subj_key - 1;



		}

		ch_sub_v.push_back(target);
		used_s++;

	}





}

void Data_Manager::refresh_priority()
{

	for (int a = 0; a < nt; a++)
	{
		if (subj_pull[a].thry_eff() < 0.80)
		{
			subj_pull[a].time_coef += 10;
		}

		if (subj_pull[a].thry_eff() > 1.20)
		{
			subj_pull[a].time_coef -= 10;
		}

		subj_pull[a].Theory_priority = 0;

		subj_pull[a].days_after_lstus_th = 0;

	}

	for (int a = nt; ( a < np + nt) && (subj_pull[a].Prac_flag == true); a++)
	{
		if (subj_pull[a].prct_eff() < 0.80)
		{
			subj_pull[a].Practice_priority *= 0.5;
		}

		if (subj_pull[a].prct_eff() > 1.20)
		{
			subj_pull[a].Practice_priority = 0;
		}

		subj_pull[a].Practice_priority *= 0.2;
		subj_pull[a].days_after_lstus_pr = 0;


	}

	for (Subject i : subj_pull)
	{

		i.Theory_priority += i.days_after_lstus_th*i.prior_coef;

		if (i.Prac_flag == true)
		{
			i.Practice_priority += i.days_after_lstus_pr*i.prior_coef;
		}
		else
		{
			i.Practice_priority = 0;
		}

	}



	

}

void Data_Manager::save_database()
{
	std::string buff(path);
	std::ofstream OUT;
	OUT.open((buff + "\\database.dat").c_str(),std::ios_base::ate);
	OUT << nt << " " << np << " " << current_day << " " << ch_sub_v.size() << " ";
	
	for (int a = 0; a < ch_sub_v.size(); a++)
	{
		OUT << ch_sub_v[a] << " ";

	}

	for (Subject i : subj_pull)
	{
		OUT << i;
	}
	
	OUT.close();

}

int Data_Manager::determine_day()
{

	time_t now = time(NULL);
	struct tm p_time ;
	localtime_s(&p_time, &now);

	return p_time.tm_wday;
	
}

void Data_Manager::assign_tasks()
{

	for (int a = 0; a < nt; a++)
	{

		subj_pull[a].assigned_th = subj_pull[a].Week_amount_theor / (7 - current_day);


	}


	for (int a = nt; a < np + nt; a++)
	{

		subj_pull[a].assigned_pr = subj_pull[a].Week_amount_pract / (7 - current_day);

		if (!subj_pull[a].Prac_flag)
		{
			subj_pull[a].assigned_pr = 0;
		}

	}


}

Data_Manager::Data_Manager()
{
	std::cout << "CRITICAL ERROR!!";

}

Data_Manager::Data_Manager(char* Path) : Manager(Path)
{
	nt = 2;
	np = 2;

}

void Data_Manager::launch()
{
	{
		char buffer[] = "\\data";
		strcat_s(path, MAX_BUF_SIZE, buffer);
	}

	this->load_database();

	if (this->determine_day() != current_day)
	{
		this->refresh_times();
		this->refresh_priority();
		this->form_day_pull();
		this->assign_tasks();
		current_day = this->determine_day();
	}




	this->save_database();




}

void Data_Manager::create_new_subj(std::string name, float priority, bool prac_flag)
{
	Subject Alex(name, priority, prac_flag);
	
	Alex.subj_key = subj_pull.size()+1;

	subj_pull.push_back(Alex);


}

void Data_Manager::show_subjs()
{
	
	for (Subject i : subj_pull)
	{
		std::cout << " " << i.subj_key << ".  " << i.Name << "\n";
		
	}

	std::cout << "\n";

}

void Data_Manager::get_sbj_commit(short unsigned int key, short unsigned int d_th, short unsigned int s_t, short unsigned int d_pr, short unsigned int sp_t)
{
	
	subj_pull[key-1].Done_theor += d_th;
	subj_pull[key-1].time_spent_th += s_t;

	subj_pull[key - 1].Done_pract += d_pr;
	subj_pull[key - 1].time_spent_pr += sp_t;

		
}

void Data_Manager::set_week_amt(short unsigned int key, short unsigned int w_th, short unsigned int w_pr)
{
	subj_pull[key - 1].Week_amount_theor = w_th;
	subj_pull[key - 1].Week_amount_pract = w_pr;

}

void Data_Manager::reset_subjs()
{
	for (Subject i : subj_pull)
	{
		Subject Buff(i.Name, i.prior_coef, i.Prac_flag);
		i = Buff;
	}
}

void Data_Manager::print_plan()
{
	std::string st_path(path);
	

	std::ofstream file;
	file.open((st_path + "\\day_plan.txt").c_str(), std::ios_base::ate);
 
	for ( int i = 0 ; i < nt; i++)
	{

		file << subj_pull[ch_sub_v[i]].Name << "\n\n" << "You are supposed to study theory in amount of: " << subj_pull[ch_sub_v[i] ].assigned_th - subj_pull[ch_sub_v[i]].Done_theor <<
			"  and your planned time is : " << subj_pull[ch_sub_v[i] ].time_coef*subj_pull[ch_sub_v[i] ].assigned_th - subj_pull[ch_sub_v[i] ].time_spent_th << " min\n\n";

	}

	for (int i = nt; i < nt + np; i++)
	{

		file << subj_pull[ch_sub_v[i] ].Name << "\n\n" << "You are supposed to do exercises in amount of: " << subj_pull[ch_sub_v[i]].assigned_pr - subj_pull[ch_sub_v[i] ].Done_pract <<
			"  and your planned time is : " << subj_pull[ch_sub_v[i] ].time_coef*subj_pull[ch_sub_v[i]].assigned_pr - subj_pull[ch_sub_v[i] ].time_spent_pr << " min\n\n";

	}

	file << "Buddy! LET'S DO THIS!! :) ";

	file.close();
}

void Data_Manager::set_day_subjects_amount(int amount_of_theory, int amount_of_practice)
{
	nt = amount_of_theory;
	np = amount_of_practice;
	ch_sub_v.resize(nt + np);

}

void Data_Manager::stop()
{
	this->save_database();
}


Data_Manager::~Data_Manager()
{
}
