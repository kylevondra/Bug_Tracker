#include "Bug.h"
#include <iostream>
#include <iomanip>

//dice1.cpp from class for rng
int dice(int num1, int num2) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(num1, num2);
	return dis(gen);
}

//function for testing if file exists
bool fexists(const char* filename) {
	std::ifstream ifile(filename);
	return (bool)ifile;
}

void Bug::generateID() {
	this->ID = dice(1, 999999);
}

Bug::Bug() {
	generateID();
}

void Bug::printBug() {

	std::cout << std::setw(6) << std::setfill('0') << ID << ", " << title << ", " << p << ", " << s << ", " << assignee << std::endl;

}

void Bug::setTitle(string title) {
	this->title = title;
}

void Bug::setPriority(int priority) {
	switch(priority) {
		case 1: this->p = priority::P1; break;
		case 2: this->p = priority::P2; break;
		default:
		case 3: this->p = priority::P3; break;
	}
}

void Bug::setStatus(int status) {
	switch(status) {
		default:
		case 1: this->s = status::NEW; break;
		case 2: this->s = status::INPROGRESS; break;
		case 3: this->s = status::COMPLETED; break;
	}
}

void Bug::setAssignee(string assignee) {
	this->assignee = assignee;
}

int Bug::getID() {
	return ID;
}

string Bug::getTitle() {
	return title;
}

priority Bug::getPriority() {
	return p;
}

status Bug::getStatus() {
	return s;
}

string Bug::getAssignee() {
	return assignee;
}