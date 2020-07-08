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

using namespace std;

void loadData(/*istream& input*/) {

}

void saveData(/*ostream& out*/) {

}

int main() {
	Grade Final("Final", 0.2);
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
	Final.removeEntry(4);
	//loadData();
	//saveData();

	return 0;
}
