#pragma once
#include "Manager.h"

#include "Media_Manager.h"

#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include <omp.h>


void Manager::get_path(char* buffer)
{
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);	
	memset(buffer, 0, MAX_BUF_SIZE);



	for (size_t i = 0; (char)path[i] != '\0'; i++)
	{
		buffer[i] = (char)path[i];
	}


	*(strrchr(buffer, '\\')) = '\0';
}

Manager::Manager()
{
	memset(path, 0, MAX_BUF_SIZE);
}

Manager::Manager(char * pPath)
{
	memset(path, 0, MAX_BUF_SIZE);
	
	strcpy_s(path, MAX_BUF_SIZE, pPath);

}




void Manager::launch()
{
	this->get_path(path);
	omp_set_num_threads(2);

#pragma omp parallel
	{

#pragma omp master
		{

			Media_Manager music(path);
			music.launch();

		}




	}


}



Manager::~Manager()
{
	memset(path, 0, MAX_BUF_SIZE);
}

