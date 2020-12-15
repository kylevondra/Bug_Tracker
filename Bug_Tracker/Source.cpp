#include <iostream>
#include "Bug.h"
#include "UIFunctions.cpp"

#define print std::cout << 

using namespace std;

std::vector<Bug> readBug() {
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

	for (int i = 0; i < temp.size(); i++) {
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
		priority d2;
			if (d == "P1") { d2 = P1; }
			else if (d == "P2") { d2 = P2; }
			else if (d == "P3") { d2 = P3; };
		status e2;
			if (e == "NEW") { e2 = NEW; }
			else if (e == "INPROGRESS") { e2 = INPROGRESS; }
			else if (e == "COMPLETED") { e2 = COMPLETED; }

		string f2 = f;

		Bug p{ b2,c2,d2,e2,f2 };
		Bugs.push_back(p);

		temp2.clear();
	}
	return Bugs;
}


int main() {
	
	//This code creates 100 random bugs
	//writes those bugs to Bugs.txt
	//Those bugs are then read from Bugs.txt and written to bugs2
	//prints the bugs
	/*
	vector<Bug*> bugs;
	vector<Bug> bugs2;

	for (int i = 0; i < 100; i++) {
		Bug a = a.rBug();
		a.printBug();
		bugs.push_back(&a);
		a.fileBug();
	};
	
	Bug a;
	bugs2 = a.readBug();

	

	cout << "\n\n\n\nREAD FROM FILE\n\n";
	
	for (int i = 0; i < bugs2.size(); i++) {
		bugs2[i].printBug();
	}*/

	vector<Bug> bugList = readBug();

	for (int i = 0; i < bugList.size(); i++) {
		bugList[i].printBug();
	}
	
	vector<Bug*> bugs;
	string input = "";
	Bug* temp;
	while(1) {
		getline(cin, input);
		input = *trim(to_lower(&input));

		if (input == "exit") { //if user entered exit
			break;
		}

		if (input == "help") {
			//TODO
			cout << "HELP MESSAGE" << endl;
		}
		else
		if ((temp = addBug(&input))) {
			bugs.push_back(temp);
		}
	}

	for (Bug* b : bugs) {
		b->printBug();
	}
	
	return 0;
}
