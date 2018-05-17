#include "Interaction_Manager.h"
#include <iostream>



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




}

void Interaction_Manager::get_command()
{
	this->print_commands();
	std::cout << std::endl << std::endl;

	std::cout << " What would you like to do next? \n";

	
	
	int command = 0;
	

		bool ok_flag = false;
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

			if (command < 5) { ok_flag = true; }
			else
			{
				std::cout << "Wrong command, please, try again:\n\n";
				
				continue;
			}

			

			switch (command)
				case 1:

		

		}

}

void Interaction_Manager::print_commands()
{

	std::cout << "Commands: \n\t 1. Update subjects info\n\t 2. Change theory/practice amount for subject\n\t 3. Add new subject\n\t" <<
		" 4. Reset all parameters to default ";

}


Interaction_Manager::~Interaction_Manager()
{
}
