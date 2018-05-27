#include "Interaction_Manager.h"
#include <iostream>
#include <string>




Interaction_Manager::Interaction_Manager(char* pPath) : Manager(pPath)
{
	Data_Manager A(pPath);
	Data = A;

}


void Interaction_Manager::launch()
{
	// determines the path where data located in
	
	Data.launch();
	
	this->get_command();
	
	Data.save();


}

void Interaction_Manager::get_command()
{
		
	
	int command = 0;
	

		bool ok_flag = false;
		std::string Name;
		while (!ok_flag)
		{
			this->print_commands();
			std::cout << std::endl << std::endl;

			std::cout << " What would you like to do next? \n";

			if (std::cin >> command) {  }
			else
			{
				std::cout << "Something went wrong, please, try again:\n\n";
				
				continue;

			}

			if (command <= 7) { }
			else
			{
				std::cout << "Wrong command, please, try again:\n\n";
				
				continue;
			}

			
			int key = 0;
			switch (command)
			{
			case 1:
				std::cout << "\n\nWhitch one? \n\n";
				Data.show_subjs();
				
				float far[2];
				int iar[2];


				std::cin >> key;
				std::cout << "\n Ok! input your info like this:\n " <<
					"'amount of theory' 'time spent' 'amount of practice' 'time spent'\n";
				std::cin >> far[0] >> iar[0] >> far[1] >> iar[1];
				std::cout << "\n Cool Buddy!! That's done! I'll keep it in mind. Hope you continue working, God bless you!";
				Data.get_sbj_commit(key, far[0], iar[0], far[1], iar[0]);
				Data.save();
				break;

			case 2:
				std::cout << "\n\nWhitch one? \n\n";
				Data.show_subjs();
				std::cin >> key;
				std::cout << "\n\nGot it!! Write amounts correspondingly:\n";
				float amou[2];
				std::cin >> amou[0] >> amou[1];
				Data.set_week_amt(key, amou[0], amou[1]);
				Data.save();
				break;

			case 3:
				std::cout <<"It's splendid!!! Give me some info about it, buddy:\n\t What is that ? ->  ";
				
				std::cin >> Name;
				std::cout << "\nOk! Great choice. It is going to be very useful!!\n Well, tell me how important this subject is and " <<
					"if there is some prictice for it? correspondingly pls (o_O)\n\n  ";
				float prir;
				int alp;
				std::cin >> prir >> alp;
				Data.create_new_subj(Name, prir, (bool)alp);
				std::cout << "\n Great!! it's done!! Let's move further!\n\n";
				Data.save();
				break;

			case 4:
				Data.reset_subjs();
				std::cout << "\n\nThat's DONE! :)  Everything is set to default.\n\n";
				Data.save();
				break;

			case 5:
				Data.print_plan();
				std::cout << "\n\nThat's DONE! :) .\n\n";
				Data.save();
				break;

			case 6:
				int a, b;
				std::cout << "Please, input numbers for theory and practice:\n ";
				std::cin >> a >> b;
				std::cout << "\n\n";
				Data.set_day_subjects_amount(a, b);
				Data.save();
				break;

			case 7 :
				Data.show_subjs();
				break;
			

			case 0:
				ok_flag = true;
				break;

			}

		

		}

}

void Interaction_Manager::print_commands()
{

	std::cout << "Commands: \n\t 1. Update subjects info\n\t 2. Change (Week) theory/practice amount for subject\n\t 3. Add new subject\n\t" <<
		" 4. Reset all parameters to default \n\t 5. Refresh day plan\n\t 6. Set amount of days tasks\n\t 7. Show Subjects\n\t 0. Save and disable \n\n";

}


Interaction_Manager::~Interaction_Manager()
{
}
