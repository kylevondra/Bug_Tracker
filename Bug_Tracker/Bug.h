#pragma once

#include <string>
#include <random>
#include <vector>
#include <fstream>
#include <sstream>

#define string std::string

typedef enum { P1, P2, P3 } priority;
typedef enum { New, InProgress, Completed } status; // enum (new, in-progress, completed)

class Bug
{
private:
	int ID; // randomly generated
	string title;
	priority p;
	status s;
	string assignee; // email

public:
	Bug() {}; // default constructor
	Bug(int ID_c, string title_c, priority priority_c, status status_c, string assignee_c) :
		ID(ID_c),
		title(title_c),
		p(priority_c),
		s(status_c),
		assignee(assignee_c) {};

	//creates random Bug for writing to file
	Bug rBug();
	void printBug();
	int fileBug(std::vector<Bug> Bugs);
};



