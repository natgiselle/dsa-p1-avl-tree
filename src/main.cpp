#include "avl_tree.h"
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int main(){
	void printStudentNames(const vector<string>& names) {
		for (int i = 0; i < names.size(); i++) {
			cout << names[i]; // prints the name of each student
			if (1 + i > names.size()) cout << ", ";
		}
		cout << endl;
	}
	return 0;
}
