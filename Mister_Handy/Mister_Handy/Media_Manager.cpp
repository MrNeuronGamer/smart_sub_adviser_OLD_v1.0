#include "Media_Manager.h"
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <windows.h>

Media_Manager::Media_Manager(char* pPath) : Manager(pPath)
{

}

void Media_Manager::launch()
{
	// determines the path where media located in
	{
		char buffer[] = "\\media";
		strcat_s(path, MAX_BUF_SIZE, buffer);
	} 

	std::vector <std::string> media_vector;	

	// fills the list of media
	{

		char buffer[MAX_BUF_SIZE];
		memset(buffer, 0, MAX_BUF_SIZE);
		strcpy_s(buffer, MAX_BUF_SIZE, path);
		strcat_s(buffer, MAX_BUF_SIZE, "\\media_list.txt");

		std::ifstream Import;
		Import.open(buffer);

		std::string str_buf;
		str_buf.clear();
		while (std::getline(Import, str_buf))
		{
			media_vector.push_back(str_buf);
			str_buf.clear();
		}

		Import.close();

	}

	// list is filled

	// starts rotating and playing music
	std::vector<std::string>::iterator iter;
	std::string st_path(path);

	for (int i = 0;; i++)
	{
		iter = media_vector.begin() + i % (media_vector.size());

		PlaySound((st_path+"\\" + (*iter)).c_str(), NULL, SND_FILENAME); //SND_FILENAME or SND_LOOP

	}


}


Media_Manager::~Media_Manager()
{
}
