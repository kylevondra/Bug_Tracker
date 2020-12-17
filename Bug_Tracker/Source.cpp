//	Kyle Vondra
//	Nicholas Simons


#include <iostream>
#include <map>
#include "Bug.h"
#include "UIFunctions.cpp"

#define print std::cout << 
#define nl std::endl

using namespace std;

#pragma region utility functions

/// <summary>
/// reads the file and returns a vector of bugs
/// </summary>
/// <returns>a vector of bugs</returns>
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
			else if (d == "P3") { d2 = P3; }
			else if (d == "1") { d2 = P1; }
			else if (d == "2") { d2 = P2; }
			else if (d == "3") { d2 = P3; };
		status e2;
			if (e == "NEW") { e2 = NEW; }
			else if (e == "INPROGRESS") { e2 = INPROGRESS; }
			else if (e == "COMPLETED") { e2 = COMPLETED; }
			else if (e == "1") { e2 = NEW; }
			else if (e == "2") { e2 = INPROGRESS; }
			else if (e == "3") { e2 = COMPLETED; };

		string f2 = f;

		Bug p{ b2,c2,d2,e2,f2 };
		Bugs.push_back(p);

		temp2.clear();
	}
	file.close();
	return Bugs;
}

/// <summary>
/// takes a pointer to a map and iterates through it
/// </summary>
/// <param name="bugMap">is the map of bugs</param>
/// <param name="searchID">is the int of the bug's ID that you want to search for</param>
/// <returns>returns a bug</returns>
Bug searchByID(map<int, Bug> *bugMap) {
	do {
		print "Enter the bug ID you would like to edit: ";
		string userInputID;
		getline(cin, userInputID);
		int inputID = stoi(userInputID);

		for (auto it = bugMap->cbegin(); it != bugMap->cend(); ++it) {
			if (it->first == inputID) {
				return it->second;
			}
		}
		print "Please enter a valid ID" << nl;
	} while (true);
	
	

}

/// <summary>
/// gets a series of user inputs and creates a new bug
/// </summary>
/// <returns>a new bug object</returns>
Bug createNewBug() {
	Bug returnBug;

	// gets description
	print "Enter a bug description: ";
	string description;
	getline(cin, description);
	returnBug.setTitle(description);

	// gets priority
	string priorityLevel;
	do {
		print "Enter a priority between 1 - 3 (1 being the least important, 3 being of highest importance): ";
		getline(cin, priorityLevel);
		if (priorityLevel == "1" || priorityLevel == "2" || priorityLevel == "3") {
			//TODO make these not ints, but P1, p2, P3
			int priorityLevelInt = stoi(priorityLevel);
			returnBug.setPriority(priorityLevelInt);
			break;
		}
		else
			print "Please enter a valid number" << nl;
	} while(true);
	

	// gets status 
	string statusLevel;
	do {
		print "Enter a status between 1 - 3 (1 being NEW, 2 being INPROGRESS, 3 being COMPLETED): ";
		getline(cin, statusLevel);
		if (statusLevel == "1" || statusLevel == "2" || statusLevel == "3") {
			// TODO make these the correct status and not an enum
			int statusLevelInt = stoi(statusLevel);
			returnBug.setStatus(statusLevelInt);
			break;
		}
		else
			print "Please enter a status\n";
	} while(true);
	

	print "Enter a assignee email: ";
	string email;
	getline(cin, email);
	returnBug.setAssignee(email);

	return returnBug;
	
}

/// <summary>
/// clears the file Bugs.txt file
/// </summary>
void clearFile() {
	std::fstream file;
	file.open("Bugs.txt", std::ios::out | std::ios::trunc);

	if (!file) {
		throw std::runtime_error("error creating file");
	}
	file.close();
}

/// <summary>
/// takes a bug, parses its information, and stores it into the file
/// </summary>
/// <param name="bug">the bug in question</param>
void putBugInFile(Bug bug) {
	std::fstream file;
	file.open("Bugs.txt", std::ios::out | std::ios::app);

	if (!file) {
		throw std::runtime_error("error creating file");
	}

	file << bug.getID() << "," << bug.getTitle() << "," << bug.getPriority() << "," << bug.getStatus() << "," << bug.getAssignee() << std::endl;
	file.close();
}

/// <summary>
/// gets the vector of bugs, loops through it, and calls the putBugInFile() function to file each bug
/// </summary>
/// <param name="bugs">the vector that stores all the bugs in the program</param>
void getBugsVectorAndStore(std::vector<Bug> bugs) {
	for (Bug b : bugs) {
		putBugInFile(b);
	};
}

/// <summary>
/// prints out the main menu 
/// </summary>
void printMenu() {
	print "\n\n===================== MENU =====================\n\n";
	print "To view all the bugs, type \"print\"" << nl;
	print "To add a new bug, type \"add\"" << nl;
	print "To edit a bug, type \"edit\"" << nl;
	print "To exit the bug tracker, type \"exit\"" << nl << nl;
	print "> ";
}

#pragma endregion

int main() {
	print "Booting up bug tracker..." << nl;

	vector<Bug> bugVec = readBug();
	map<int, Bug> bugMap;

	// adds bugs to map (could probably extract to a method, but no time)
	for (int i = 0; i < bugVec.size(); i++) {
		bugMap.insert(pair<int, Bug>(bugVec[i].getID(), bugVec[i]));
	}

	string input = "";

	while(1) {

		printMenu();

		
		getline(cin, input);
		input = *trim(to_lower(&input));

		if (input == "exit") { 
			clearFile();
			getBugsVectorAndStore(bugVec);
			break;
		}

		if (input == "edit") {
			Bug result = searchByID(&bugMap);
			print "What would you like to edit? (description, priority, status, assignee): ";
			string userWantsToEdit;
			getline(cin, userWantsToEdit);

			if (userWantsToEdit == "description") {
				print "Please enter the new title: ";
				string newTitle;
				getline(cin, newTitle);
				result.setTitle(newTitle);
				print "Title updated!" << nl;
			}
			else if (userWantsToEdit == "priority") {
				print "Please enter the new priority level: ";
				string newPriority;
				getline(cin, newPriority);
				int newPriorityInt = stoi(newPriority);
				result.setPriority(newPriorityInt);
				print "Priority updated!" << nl;
			}
			else if (userWantsToEdit == "status") {
				print "Please enter the new status level: ";
				string newStatus;
				getline(cin, newStatus);
				int newStatusInt = stoi(newStatus);
				result.setPriority(newStatusInt);
				print "Status updated!" << nl;
			}
			else if (userWantsToEdit == "assignee") {
				print "Please enter the new assignee: ";
				string newAssignee;
				getline(cin, newAssignee);
				result.setTitle(newAssignee);
				print "Title updated!" << nl;
			}
			else {
				print "Please enter a valid input" << nl;
			}
			
			// removes the old bug from the map and inserts the updated bug
			bugMap.erase(result.getID());
			bugMap.insert(pair<int, Bug>(result.getID(), result));
			
			// finds the bug in the vector
			for (auto it = bugVec.begin(); it != bugVec.end(); ++it) {
				if (result.getID() == it->getID()) {
					bugVec.erase(it);
					bugVec.push_back(result);
				}
			}

			
			

			
		}

		if (input == "add") {
			Bug newBug = createNewBug();
			bugVec.push_back(newBug);
			bugMap.insert(pair<int, Bug>(newBug.getID(), newBug));
			print "Bug added! \n";
		}

		if (input == "print")
		{
			print "\nCurrently tracked bugs: \n\n";
			for (int i = 0; i < bugVec.size(); i++) {
				bugVec[i].printBug();
			}
		}

		
	}
	
	print "Exiting bug tracker..." << nl;
	return 0;
}
