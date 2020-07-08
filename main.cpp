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

void error(string message, bool test) {
	if (test) {
		cout << "Error: " << message << endl;
	}
}

string loadData(string username, string password, vector<Grade> Syllabus) {
	cout << "Loading Syllabus... " << endl;
	bool loop1 = true;
	string filename;
	while (loop1) {
		string classname, initials;
		cout << "Enter the name for your class: " << endl;
		getline(cin, classname);
		cout << "Enter your initials: " << endl;
		getline(cin, initials);
		filename = classname + "-" + initials + ".txt";
		//filename = "CSCE222-SD.txt";
		ifstream inFile(filename);
		if (!inFile) {
			string check;
			cout << "No existing file for this combination of Class Name and initials was found." << endl;
			cout << "Would you like to create a new file? (y - lowercase only - for yes, anything else for no): " << endl;
			getline(cin, check);
			if (check == "y") {
				cout << "Enter the username for the new file: " << endl;
				getline(cin, username);
				cout << "Enter the password for the new file: " << endl;
				getline(cin, password);
				return filename;
			}
			else {
				cout << "Would you like to quit the program? (y - lowercase only - for yes, anything else for no): " << endl;
				getline(cin, check);
				if (check == "y") exit(1);
			}
		}
		else {
			loop1 = false;
			string un, pw;
			while (!inFile.eof()) {
				string un, pw, line;
				getline(inFile, un);
				getline(inFile, pw);
				getline(inFile, line, '\r');
				cout << "Line: " << line << endl;
				istringstream ss(line);

				bool loop2 = true;
				do {
					cout << "Enter your username" << endl;
					getline(cin, username);
					cout << "Enter your password" << endl;
					getline(cin, password);
					//username = "username";
					//password = "password";
					if (username.compare(un) == 0 && password.compare(pw) == 0) {
						cout << "Valid Credentials Entered. The Program will continue to load." << endl;
						loop2 = false;
					}
					else {
						string check;
						/*cout << "Guess: U = " << username << ", P = " << password << endl;
						cout << "Actual: U = " << un << ", P = " << pw << endl;*/
						cout << "Invalid Credentials Entered. Would you like to try again? (y - lowercase only - for yes, anything else for no): " << endl;
						getline(cin, check);
						if (check != "y") exit(1);
					}
				} while (loop2);

				string name, w, e;
				while (ss >> name >> w >> e) {
					error("Other invalid input", (name == "" || w == "" || e == ""));
					cout << "Pushing Back new grade..." << endl;
					Syllabus.push_back(Grade(name, stof(w)));
					cout << "Inserted new grade: " << Syllabus.back();
					while (e != "-1") {
						cout << "Inserting key " << e << "... " << endl;
						Syllabus.back().insertEntry(stof(e));
						ss >> e;
					}
				}
			}
		}
	}
	return filename;
}

void saveData(string username, string password, string filename, vector<Grade> Syllabus) {

}

int main() {
	/*Grade Final("Final", 0.2);
	cout << "Initial Grade Object: " << endl << Final << endl;
	Final.insertEntry(100);
	Final.insertEntry(99);
	Final.insertEntry(95.5);
	Final.insertEntry(0);
	Final.insertEntry(100);
	Final.insertEntry(98);
	Final.insertEntry(96);
	Final.insertEntry(97);
	Final.insertEntry(97);
	Final.insertEntry(0);
	cout << "Grade Object After 10 Insertions: " << endl << Final << endl;
	Final.removeEntry(-1);
	Final.removeEntry(10);
	Final.removeEntry(9);
	Final.removeEntry(0);
	Final.removeEntry(4);*/

	vector<Grade> Syllabus;
	string username = "";
	string password = "";

	string filename = loadData(username, password, Syllabus);
	for (Grade g : Syllabus) {
		cout << g << endl;
	}

	modifyData();

	saveData(username, password, filename, Syllabus);

	system("pause");
	return 0;
}
