#pragma once
#include "Manager.h"
#include <string>
#include <vector>
#include "Subject.h"


class Data_Manager :

	public Manager
{
private:

	std::vector<class Subject> subj_pull;	/// The pull of Subjects
	int nt;									/// Number of theory slots
	int np;									/// Number of practice slots
	std::vector<int> ch_sub_v;				/// Pull of indexes of chosen subjects

	int current_day;

	void refresh_times();
	void load_database();
	void form_day_pull();
	void refresh_priority();
	void save_database();
	int determine_day();
	void assign_tasks();
	

	



public:
	Data_Manager();
	Data_Manager(char* Path);
	void launch();
	void create_new_subj(std::string name, float priority, bool prac_falg );
	void show_subjs();
	void get_sbj_commit(int key, float d_th, int s_t, float d_pr,  int sp_t);
	void set_week_amt(int key, float w_th, float w_pr);
	void reset_subjs();
	void print_plan();
	void set_day_subjects_amount(int amount_of_theory, int amount_of_practice);
	void save();
	~Data_Manager();
};

