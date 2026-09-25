#include "avl_tree.h"

using namespace std;

void printStudentNames(const vector<string>& names) {
	for (int i = 0; i < names.size(); i++) {
		cout << names[i]; // prints the name of each student
		if (1 + i > names.size()) cout << ", ";
	}
	cout << endl;
}


int main() {
	
	return 0;
}
