//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//								MAIN FILE									//
//								MAIN.CPP									//
//																			//
//	Date: 6/JUL/2020														//
//	Author: Sean Duffie														//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "grade.h"

#include <sstream>
#include <fstream>

using namespace std;

// Templated Error Message Function
void error(string message, bool test) {
	if (test) {
		cout << "Error: " << message << endl;
	}
}

// Function Parameters - Funtion to load in data from a text file and populate parameters
string loadData(string username, string password, vector<Grade> Syllabus) {
	cout << "Loading Syllabus... " << endl;
	bool loop1 = true; // Loop to allow user to try again when the file they enter is not found
	string filename; // Name of the file to be read from - or created if not found - and eventually outputted to

	while (loop1) {
		string classname, initials; // Variable used for the filename
		cout << "Enter the name for your class: " << endl;
		getline(cin, classname);
		cout << "Enter your initials: " << endl;
		getline(cin, initials);
		filename = classname + "-" + initials + ".txt";
		//filename = "CSCE222-SD.txt";
		ifstream inFile(filename); // Input file - format is structured like "[Class]-[user initials].txt".

		if (!inFile) {
			string check; // Option to create a new file, try again, or quit the program
			cout << "No existing file for this combination of Class Name and initials was found." << endl;
			cout << "Would you like to create a new file? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") { // Try again
				cout << "Enter the username for the new file: " << endl;
				getline(cin, username);
				cout << "Enter the password for the new file: " << endl;
				getline(cin, password);
				return filename;
			}
			else { // Prompt to quit
				cout << "Would you like to quit the program? (y - lowercase only - for yes, anything else for no): " << endl;
				getline(cin, check);
				if (check == "y") exit(1);
			}
		}
		else {
			loop1 = false;
			string un, pw; // Correct Credentials Acquired from the file
			// Loop to cycle through the data in the file
			while (!inFile.eof()) {
				string un, pw, line;
				getline(inFile, un);
				getline(inFile, pw);
				getline(inFile, line, '\r');
				istringstream ss(line); // Breaks the data from the text file into components

				bool loop2 = true; // Acquires Credentials from the user and verifies them
				do {
					cout << "Enter your username" << endl;
					getline(cin, username);
					cout << "Enter your password" << endl;
					getline(cin, password);
					//username = "username";
					//password = "password";
					// Successful Validation
					if (username.compare(un) == 0 && password.compare(pw) == 0) {
						cout << "Valid Credentials Entered. The Program will continue to load." << endl;
						loop2 = false;
					}
					// Incorrect username or password, gives option to try again or quit
					else {
						string check; // Option to quit or retry
						cout << "Invalid Credentials Entered. Would you like to try again? (y - lowercase only - for yes, anything else for no): " << endl;
						getline(cin, check);
						if (check != "y") exit(1);
					}
				} while (loop2);

				string name, w, e; // Variable of the new Grade Object
				// Loop to cycle through each new Grade Object found in the text file
				while (ss >> name >> w >> e) {
					error("Other invalid input", (name == "" || w == "" || e == ""));
					cout << "Pushing Back new grade..." << endl;
					Syllabus.push_back(Grade(name, stof(w)));
					cout << "Inserted new grade: " << Syllabus.back().name << " of weight " << Syllabus.back().wt << endl;
					while (e != "-1") {
						Syllabus.back().insertEntry(stof(e));
						ss >> e;
					}
				}
			}
		}
	}
	return filename;
}

void modifyData(vector<Grade> Syllabus) {
	// Prompt to add a new Grade Object to the Syllabus

	// Loop through each Grade Object in the Syllabus
	/*for (Grade g : Syllabus) {
		// Add any new entries to the grade
		bool loop1 = true;
		while (loop1) {
			string check;
			cout << "Do you want to add a new entry to the " << g.name << " category? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") {
				string entry;
				cout << "Enter the grade that you want to insert into the " << g.name << " category: " << endl;
				getline()
			}
			else
		}
		// Print all current entries in the grade, with an index included
		// Prompt the user to pick an entry to remove
	}*/
}

void saveData(string username, string password, string filename, vector<Grade> Syllabus) {

}

int main() {

	vector<Grade> Syllabus; // Vector used to store all the elements of a Grade Object
	string username, password; // Credentials Acquired from the user. Validated to be true after passed through "loadData()".

	string filename = loadData(username, password, Syllabus); // Name of the file to be read from - or created if not found - and eventually outputted to
	for (Grade g : Syllabus) { cout << g << endl; }

	modifyData(Syllabus);

	saveData(username, password, filename, Syllabus);

	system("pause");
	return 0;
}
