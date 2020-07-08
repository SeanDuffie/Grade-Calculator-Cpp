//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//							GRADE HEADER									//
//							  GRADE.H										//
//																			//
//	Date: 6/JUL/2020														//
//	Author: Sean Duffie														//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifndef GRADE_H
#define GRADE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

//
struct Grade {
	string name; // Name of Grade type
	float wt; // Overall weight of the type of grade
	vector<float> v; // Vector of entries sorted in ascending order
	int amnt; // Expected amount of entries that have not been entered (optional)
	bool fin; // Set to true when user says there are no more elements to add
	//void setWeight(float w); // Function to modify the existing value for the weight
	//void setAmnt(int a); // Function to modify the expected amount of additional entries
	void insertEntry(float entry); // insertEntry(float entry) - inserts a float in the sorted vector - Runtime O(n)
	bool removeEntry(int index); // removeEntry(int index) - removes the element in the vector at a given point - Runtime O(n)
	Grade(string n = " ", float w = 0.1, bool f = false) : name(n), wt(w), v(), amnt(0), fin(f) {}; // Default Constructor
};

// insertEntry(float entry) - inserts a float in the sorted vector - Runtime O(n)
void Grade::insertEntry(float e) {
	if (v.empty()) v.push_back(e);
	else {
		bool check = false;
		for (int i = 0; i < v.size() && !check; i++) {
			if (e < *(v.begin() + i)) { v.insert(v.begin() + i, e); check = true; }
		}
		if (!check) v.push_back(e);
	}
}

// removeEntry(int index) - removes the element in the vector at a given point - Runtime O(n)
bool Grade::removeEntry(int index) {
	if (index < 0) {
		cout << "Error: index must be a positive integer." << endl;
		return false;
	}
	else if (index >= v.size()) {
		cout << "Error: index must be less than the size of the vector." << endl;
		return false;
	}
	else {
		cout << "Vector before removing:" << endl;
		for (int i = 0; i < v.size(); i++) cout << v[i] << endl;
		cout << "Removing the element at index " << index << ": (" << v[index] << ")" << endl;
		v.erase(v.begin() + index);
		cout << "Vector after removing:" << endl;
		for (float temp : v) cout << temp << endl;
		return true;
	}
}

// operator<<(ostream& out, Grade& g) - Outputs the Grade "g" (right hand operator) to the output stream "out" (left hand operator) - Runtime O(n)
ostream& operator<<(ostream& out, Grade& g) {
	out << g.name << "\n";
	out << g.wt << "\n";
	out << g.fin << "\n";
	for (float e : g.v) { out << e << "\n"; }
	out << -1 << "\n";
	return out;
}

#endif // !GRADE_H
