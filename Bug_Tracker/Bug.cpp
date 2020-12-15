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

Bug Bug::rBug() {
	//list of names(n), emails(e), and titles(t)
	//concatonate each one to create random emails for the file, add more if you want
	std::vector<string> n{ "Bob", "Steven", "Joshua45", "CSS445", "RobertsR", "Jeff", "Nich", "Zach", "Nate", "Donovan" };
	std::vector<string> e{ "@yahoo.com", "@gmail.com", "@aol.net", "@hotmail.com" };
	std::vector<string> t{ "Code does not compile", "Syntax error", "There is no text in code", "There are literal bugs in the server", "Wrong coding language" };


	return Bug(dice(1, 999999), t[dice(0, t.size() - 1)], priority(dice(0, 2)), status(dice(0, 2)), n[dice(0, n.size() - 1)] + e[dice(0, e.size() - 1)]);
}

void Bug::printBug() {

	//this code adds 0s to front of id to make it 6 digits when displayed
	/*
	string i = std::to_string(ID);
	if (ID < 99999) {
		if (ID > 9999) {
			i = "0" + i;
		}
		else if (ID > 999) {
			i = "00" + i;
		}
		else if (ID > 99) {
			i = "000" + i;
		}
		else if (ID > 9) {
			i = "0000" + i;
		}
		else { i = "00000" + i; }
	}
	*/

	//actual print statement
	//setw and setfill do same as above
	std::cout << std::setw(6) << std::setfill('0') << ID << ", " << title << ", ";// << p << ", " << s << ", " << assignee << std::endl;

	//prints priority
	switch (p) {
	case 0:
		std::cout << "Priority 1, ";
		break;
	case 1:
		std::cout << "Priority 2, ";
		break;
	case 2:
		std::cout << "Priority 3, ";
		break;
	};

	//prints status
	switch (s) {
	case 0:
		std::cout << "New, ";
		break;
	case 1:
		std::cout << "In Progress, ";
		break;
	case 2:
		std::cout << "Completed, ";
		break;
	}
	//finishes print statement
	std::cout << assignee << std::endl;
}

//Write to file
void Bug::fileBug() {
	std::fstream file;
	file.open("Bugs.txt", std::ios::out | std::ios::app);

	if (!file) {
		throw std::runtime_error("error creating file");
	}

	file << this->ID << "," << this->title << "," << this->p << "," << this->s << "," << this->assignee << std::endl;
	file.close();
}




//read from file

std::vector<Bug> Bug::readBug() {
	string line, word;
	std::vector<string> temp;
	std::vector<Bug> Bugs;

	//open and test bugs.txt
	std::ifstream file("Bugs.txt");
	if (!file.is_open()) {
		throw std::runtime_error("Could not open file Bugs.txt");
	}

	//add all strings in bugs.txt seperated by comma to temp vector
	if (file.good()) {
		while (std::getline(file, line)) {
			std::stringstream s(line);
			while (std::getline(s, word)) {
				temp.push_back(word);
			}
		}
	}

	for (int i = 1; i < temp.size(); i++) {
		string a, b, c, d, e, f;

		std::vector<string>temp2;
		a = temp[i];
		std::stringstream s_stream(a);
		while (s_stream.good()) {
			string substr;
			std::getline(s_stream, substr, ',');
			temp2.push_back(substr);
		}

		b = temp2[0];
		c = temp2[1];
		d = temp2[2];
		e = temp2[3];
		f = temp2[4];

		int b2 = stoi(b);
		string c2 = c;
		priority d2 = priority(stoi(d));
		status e2 = status(stoi(e));
		string f2 = f;

		Bug p{ b2,c2,d2,e2,f2 };
		Bugs.push_back(p);

		temp2.clear();
	}
	return Bugs;
}




void Bug::fileBug(std::vector<Bug*> bugs) {
	for (Bug* b : bugs) {
		b->fileBug();
	};
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
