#pragma once
#ifndef MAX_BUF_SIZE
#define MAX_BUF_SIZE (3*1024)
#endif

class Manager
{
private:
	void get_path(char* pPath);
protected:
	char path[MAX_BUF_SIZE];	


public:
	Manager();
	Manager(char* pPath);
	
	
	virtual void launch();

	~Manager();
};

