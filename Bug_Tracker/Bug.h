#pragma once

#include <string>
#include <random>

#define string std::string

class Bug
{
private:
	int ID; // randomly generated
	string Title;
	int priority; // enum (P0, P1, P2)
	int status; // enum (new, in-progress, completed)
	string assignee; // email

private:
	
};


