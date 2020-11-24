#pragma once

#include <string>
#include <random>

#define string std::string

class Bug
{
private:
	int ID; // randomly generated
	string title;
	int priority; // enum (P0, P1, P2)
	int status; // enum (new, in-progress, completed)
	string assignee; // email

public:
	Bug() {}; // default constructor
	Bug(int ID_c, string title_c, int priority_c, int status_c, string assignee_c) : 
		ID(ID_c), 
		title(title_c), 
		priority(priority_c), 
		status(status_c), 
		assignee(assignee_c) {};

	
};


