#include <iostream>
#include "Bug.h"
#include "UIFunctions.cpp"

using namespace std;

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
