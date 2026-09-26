
#include <sstream>
#include <string>
#include "avl_tree.h"
using namespace std;

void printStudentNames(const vector<string>& names) {
	for (int i = 0; i < names.size(); i++) {
		cout << names[i]; // prints the name of each student
		if (i + 1 < names.size()) cout << ", ";
	}
	cout << endl;
}


int main() {
	AVLTree tree;
	// get the lines from the user inpt and m
	string lineCt;
	getline(cin, lineCt);
	int lineTotal = stoi(lineCt);

	for(size_t i = 0; i < lineTotal; i++) {
		string line;
		getline(cin, line);

		istringstream in(line);
		string command;
		in >> command;

		if (command == "insert") {
			string discard, name, strId;
			getline(in, discard, '"');
			getline(in, name, '"');
			in >> strId;
			if (tree.insert(name, strId)) cout << "succesful";
			else {
			cout << "unsuccessful";
			}
		}

		else if (command == "remove") {
			string discard, strId;
			getline(in, discard, '"');
			getline(in, strId, '"');
			in >> strId;
			if(tree.remove(strId)) cout << "successful";
			else {
				cout << "unsuccessful";
			}
		}
	}

	return 0;
}
