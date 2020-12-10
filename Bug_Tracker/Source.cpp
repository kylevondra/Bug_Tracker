#include <iostream>
#include "Bug.h"
#include "UIFunctions.cpp"

using namespace std;

int main() {
	/*
	vector<Bug*> bugs;
	for (int i = 0; i < 100; i++) {
		Bug a = a.rBug();
		a.printBug();
		bugs.push_back(&a);
		a.fileBug();
	};
	*/

	//Bug b = b.rBug();
	//b.fileBug(Bugs);

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
