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
string loadData(string& username, string& password, vector<Grade>& Syllabus) {
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

				string name, w, f, e; // Variable of the new Grade Object
				// Loop to cycle through each new Grade Object found in the text file
				while (ss >> name >> w >> f >> e) {
					error("Other invalid input", (name == "" || f == "" || w == "" || e == ""));
					cout << "Pushing Back new grade..." << endl;
					Syllabus.push_back(Grade(name, stof(w), stoi(f)));
					cout << "Inserted new grade: " << Syllabus.back().name << " of weight " << Syllabus.back().wt << ". This type is finished: " << Syllabus.back().fin << endl;
					while (e != "-1") {
						Syllabus.back().insertEntry(stof(e));
						ss >> e;
					}
				}
				ss.clear(); // Empty the stringstream
			}
			inFile.close(); // Close the input file
		}
	}
	return filename;
}

// Function Parameters - Function to allow the user to modify the existing data or to add new data
void modifyData(string& username, string& password, string& filename, vector<Grade>& Syllabus) {
	// Prompt to change username or password
	string check; // String to test user input
	cout << "Would you like to change your username? (y - lowercase only - for yes, anything else for no): " << endl;
	getline(cin, check);
	if (check == "y") {
		cout << "Enter your new username: " << endl;
		getline(cin, username);
	}
	cout << "Would you like to change your password? (y - lowercase only - for yes, anything else for no): " << endl;
	getline(cin, check);
	if (check == "y") {
		cout << "Enter your new password: " << endl;
		getline(cin, password);
	}

	// Prompt to add a new Grade Object to the Syllabus
	bool loop1 = true;
	while (loop1) {
		cout << "Would you like to add a new type of Grade? (y - lowercase only - for yes, anything else for no): " << endl;
		getline(cin, check);
		if (check != "y") loop1 = false;
		else {
			string name, wt, fin, entry;
			cout << "Enter the name of the new Grade Object: " << endl;
			getline(cin, name);
			cout << "Enter the weight of this Grade Object: " << endl;
			getline(cin, wt);
			Syllabus.push_back(Grade(name, stof(wt)));
			do {
				cout << "Enter a float for an entry: " << endl;
				getline(cin, entry);
				if (entry != "-1") Syllabus.back().insertEntry(stof(entry));
			} while (entry != "-1");
			cout << "Is this list finished? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") Syllabus.back().fin = true;
		}
	}

	// Loop through each Grade Object in the Syllabus
	for (Grade g : Syllabus) {
		bool loop1 = true;
		while (loop1) {
			// Print all current entries in the grade, with an index included
			cout << "Current Grade Type: " << endl;
			cout << "Name - " << g.name << endl
				 << "Weight - " << g.wt << endl
				 << "Finished - " << g.fin << endl
				 << "Entries: " << endl;
			for (int i = 1; i <= g.v.size(); i++) { cout << i << ". " << g.v[i - 1] << endl; }

			string check;

			// Add any new entries to the grade
			cout << "Do you want to add a new entry to the " << g.name << " category? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") {
				string entry;
				cout << "Enter the grade that you want to insert into the " << g.name << " category: " << endl;
				getline(cin, entry);
				g.insertEntry(stof(entry));
			}

			// Print all current entries in the grade, with an index included
			cout << "Current Grade Type: " << endl;
			cout << "Name - " << g.name << endl
				 << "Weight - " << g.wt << endl
				 << "Finished - " << g.fin << endl
				 << "Entries: " << endl;
			for (int i = 1; i <= g.v.size(); i++)
			{
				cout << i << ". " << g.v[i - 1] << endl;
			}

			// Remove existing entries from the grade
			cout << "Do you want to remove an entry from the " << g.name << " category? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") {
				string index;
				cout << "Enter the index of the grade you want to remove: " << endl;
				getline(cin, index);
				g.removeEntry(stoi(index)-1);
			}

			// Prompt to end loop
			cout << "Do you want to end this loop? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") loop1 = false;
		}
	}
}

// Function Parameters - Function to output the loaded, processed, and possibly modified data back into the original file
void saveData(string username, string password, string filename, vector<Grade> Syllabus) {
	cout << "Saving Syllabus..." << endl;
	// Open the file or create a new file with the given filename
	ofstream outFile(filename); // Output file - generated from the filename text file.
	if (!outFile.is_open()) error("Unable to open file", true);
	else {
		cout << "Populating Header..." << endl;
		cout << "  Adding username = '" << username << "' and password = '" << password << "'." << endl;
		outFile << username << "\n"
				<< password << "\n"; // Output the data in the header information (username, password, fin)
		// Output the data for each Grade Object
		for (Grade g : Syllabus) {
			cout << "  Adding Grade: " << g;
			outFile << g;
		}
	}
	outFile.close(); // Close the output file
}

// Function Parameters - Function to perform all the calculations on the current Syllabus
void performCalculations() {
	// Loop to allow user to repeat this function
		// Loop through each Grade and prompts user for the amount of expected future entries
		// Calculate the average of all entries for each Grade Object and store it in a separate vector (of the same size of the Syllabus)
			// Repeat this process with a new vector for the several different configurations:
		// For each vector of average entries, find the sum of each average multiplied by it's respective weight
		// Each of the sums are different grade results, print all to console with descriptions
}

int main() {

	vector<Grade> Syllabus; // Vector used to store all the elements of a Grade Object
	string username, password; // Credentials Acquired from the user. Validated to be true after passed through "loadData()".

	string filename = loadData(username, password, Syllabus); // Name of the file to be read from - or created if not found - and eventually outputted to
	for (Grade g : Syllabus) { cout << g << endl; }

	modifyData(username, password, filename, Syllabus);

	saveData(username, password, filename, Syllabus);

	performCalculations();

	system("pause");
	return 0;
}
