#include "Interaction_Manager.h"
#include <iostream>
#include <string>




Interaction_Manager::Interaction_Manager(char* pPath) : Manager(pPath)
{
}


void Interaction_Manager::launch()
{
	// determines the path where data located in
	{
		char buffer[] = "\\data";
		strcat_s(path, MAX_BUF_SIZE, buffer);
	}

	while (true)
	{
		this->get_command();
	}



}

void Interaction_Manager::get_command()
{
	this->print_commands();
	std::cout << std::endl << std::endl;

	std::cout << " What would you like to do next? \n";

	
	
	int command = 0;
	

		bool ok_flag = false;
		std::string Name;
		while (!ok_flag)
		{
			this->print_commands();
			std::cout << std::endl << std::endl;

			std::cout << " What would you like to do next? \n";

			if (std::cin >> command) { ok_flag = true; }
			else
			{
				std::cout << "Something went wrong, please, try again:\n\n";
				
				continue;

			}

			if (command < 6) { ok_flag = true; }
			else
			{
				std::cout << "Wrong command, please, try again:\n\n";
				
				continue;
			}

			
			short unsigned int key = 0;
			switch (command)
			{
			case 1:
				std::cout << "\n\nWhitch one? \n\n";
				Data.show_subjs();
				
				short unsigned int work_arr[4];


				std::cin >> key;
				std::cout << "\n Ok! input your info like this:\n " <<
					"'amount of theory' 'time spent' 'amount of practice' 'time spent'\n";
				std::cin >> work_arr[0] >> work_arr[1] >> work_arr[2] >> work_arr[3];
				std::cout << "\n Cool Buddy!! That's done! I'll keep it in mind. Hope you continue working, God bless you!";
				Data.get_sbj_commit(key, work_arr[0], work_arr[1], work_arr[2], work_arr[3]);
				break;

			case 2:
				std::cout << "\n\nWhitch one? \n\n";
				Data.show_subjs();
				std::cin >> key;
				std::cout << "\n\nGot it!! Write amounts correspondingly:\n";
				short unsigned int amou[2];
				std::cin >> amou[0] >> amou[1];
				Data.set_week_amo(key, amou[0], amou[1]);
				break;

			case 3:
				std::cout <<"It's splendid!!! Give me some info about it, buddy:\n\t What is that ? ->  ";
				
				std::getline(std::cin, Name);
				std::cout << "Ok! Great choice. It is going to be very useful!!\n Well, tell me how important this subject is and " <<
					"if there is some prictice for it? correspondingly pls (o_O)\n\n  ";
				float prir;
				int alp;
				std::cin >> prir >> alp;
				Data.create_new_subj(Name, prir, (bool)alp);
				std::cout << "\n Great!! it's done!! Let's move further!\n\n";
				break;

			case 4:
				Data.reset_subjs();
				std::cout << "\n\nThat's DONE! :)  Everything is set to default.\n\n";
				break;

			case 5:
				Data.refresh_plan();
				std::cout << "\n\nThat's DONE! :)  Everything is set to default.\n\n";

			case 0:
				break;

			}

		

		}

}

void Interaction_Manager::print_commands()
{

	std::cout << "Commands: \n\t 1. Update subjects info\n\t 2. Change (Week) theory/practice amount for subject\n\t 3. Add new subject\n\t" <<
		" 4. Reset all parameters to default \n\t 5. Refresh day plan\n\t 0. Back\n\n";

}


Interaction_Manager::~Interaction_Manager()
{
}
