#include "Data_Manager.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>







void Data_Manager::refresh_times()
{
	for (int i = 0 ; i < subj_pull.size(); i++)
	{
		subj_pull[i].days_after_lstus_pr += 1;
		subj_pull[i].days_after_lstus_th += 1;
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
	ch_sub_v.clear();
	ch_sub_v.reserve(size_v);
	subj_pull.clear();

	for (int a = 0; a < size_v; a++)
	{
		int buf;
		IN >> buf;
		ch_sub_v.push_back(buf);

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
	ch_sub_v.clear();
	ch_sub_v.reserve(nt + np);
	short int used_s = 0;
	bool first = true;
	int target = 0;

	for (int a = 0; a < nt; a++)
	{
		first = true;
		if (used_s == subj_pull.size()) break;

		for (Subject i : subj_pull)
		{

			if (std::find(ch_sub_v.begin(), ch_sub_v.end(), (i.subj_key - 1)) != ch_sub_v.end()) continue;

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
		
		if (subj_pull[ch_sub_v[a]].thry_eff() < 0.80)
		{
			subj_pull[ch_sub_v[a]].time_coef += 5;
		}

		if (subj_pull[ch_sub_v[a]].thry_eff() > 1.20)
		{
			subj_pull[ch_sub_v[a]].time_coef -= 5;
		}

		subj_pull[ch_sub_v[a]].Week_amount_theor -= subj_pull[ch_sub_v[a]].Done_theor;

		subj_pull[ch_sub_v[a]].Theory_priority = 0;
		subj_pull[ch_sub_v[a]].Done_theor = 0;
		subj_pull[ch_sub_v[a]].time_spent_th = 0;

		subj_pull[ch_sub_v[a]].days_after_lstus_th = 0;

	}

	for (int a = nt; ( a < np + nt) && (subj_pull[ch_sub_v[a]].Prac_flag); a++)
	{
		if (subj_pull[ch_sub_v[a]].prct_eff() < 0.80)
		{
			subj_pull[ch_sub_v[a]].Practice_priority *= 0.5;
		}

		if (subj_pull[ch_sub_v[a]].prct_eff() > 1.20)
		{
			subj_pull[ch_sub_v[a]].Practice_priority = 0;
		}

		subj_pull[ch_sub_v[a]].Week_amount_pract -= subj_pull[ch_sub_v[a]].Done_pract;

		subj_pull[ch_sub_v[a]].Practice_priority *= 0.2;
		subj_pull[ch_sub_v[a]].days_after_lstus_pr = 0;
		subj_pull[ch_sub_v[a]].Done_pract = 0;
		subj_pull[ch_sub_v[a]].time_spent_pr = 0;


	}

	for (int i = 0; i < subj_pull.size(); i++)
	{

		subj_pull[i].Theory_priority += subj_pull[i].days_after_lstus_th*subj_pull[i].prior_coef;

		if (subj_pull[i].Prac_flag == true)
		{
			subj_pull[i].Practice_priority += subj_pull[i].days_after_lstus_pr*subj_pull[i].prior_coef;
		}
		else
		{
			subj_pull[i].Practice_priority = 0;
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

		subj_pull[ch_sub_v[a]].assigned_th = subj_pull[ch_sub_v[a]].Week_amount_theor / (7 - current_day);


	}


	for (int a = nt; a < np + nt; a++)
	{

		subj_pull[ch_sub_v[a]].assigned_pr = subj_pull[ch_sub_v[a]].Week_amount_pract / (7 - current_day);

		if (!subj_pull[ch_sub_v[a]].Prac_flag)
		{
			subj_pull[ch_sub_v[a]].assigned_pr = 0;
		}

	}


}

Data_Manager::Data_Manager()
{
	std::cout << "CRITICAL ERROR!!";

}

Data_Manager::Data_Manager(char* Path) : Manager(Path)
{
	

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
		current_day = this->determine_day();
		this->assign_tasks();
		
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

void Data_Manager::get_sbj_commit(int key, float d_th, int s_t, float d_pr,  int sp_t)
{
	
	subj_pull[key-1].Done_theor += d_th;
	subj_pull[key-1].time_spent_th += s_t;

	subj_pull[key - 1].Done_pract += d_pr;
	subj_pull[key - 1].time_spent_pr += sp_t;

		
}

void Data_Manager::set_week_amt(int key, float w_th, float w_pr)
{
	subj_pull[key - 1].Week_amount_theor = w_th;
	subj_pull[key - 1].Week_amount_pract = w_pr;

}

void Data_Manager::reset_subjs()
{
	for (int i = 0; i < subj_pull.size(); i++)
	{
		Subject Buff(subj_pull[i].Name, subj_pull[i].prior_coef, subj_pull[i].Prac_flag);
		subj_pull[i] = Buff;
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
	this->form_day_pull();

}

void Data_Manager::save()
{
	this->save_database();
}


Data_Manager::~Data_Manager()
{
}
