
#include <sstream>
#include <string>
#include "avl_tree.h"
using namespace std;

void printStudentNames(const vector<string>& names) {
	for (size_t i = 0; i < names.size(); i++) {
		cout << names[i]; // prints the name of each student
		if (i + 1 < names.size()) cout << ", ";
	}
	cout << endl;
}


int main() {
	AVLTree tree;
	// get the input from user input
	string lineCt;
	getline(cin, lineCt);
	int lineTotal = stoi(lineCt);

	for(int i = 0; i < lineTotal; i++) {
		string line;
		getline(cin, line);

		istringstream in(line);
		string command;
		in >> command;
		
		// makes it so that the user can use the insert function,remove function , etc.
		if (command == "insert") {
			string discard, name, strId;
			getline(in, discard, '"');
			getline(in, name, '"');
			in >> strId;
			if (tree.insert(name, strId)) cout << "successful\n";
			else {
			cout << "unsuccessful\n";
			}
		}

		else if (command == "remove") {
			string strId;
			in >> strId;
			if(tree.remove(strId)) cout << "successful\n";
			else {
				cout << "unsuccessful\n";
			}
		}

		else if (command == "removeInorder") {
			// needs to ensure that the N is only digits
			string n;
			in >> n;
			bool isNum = !n.empty();
			for (char c : n) {
				if (c < '0' || c > '9') isNum = false;
			}
			if (isNum && tree.removeInorder(stoi(n))) cout << "successful\n";
			else cout << "unsuccessful\n";
		}

		else if (command == "search") {
			string str;	
			// ws for whitespace!
			getline(in >> ws, str);

			// the double quotes are taken off to extract the name
			if (str.size() >= 2 && str.front() == '"' && str.back() == '"') {
				string name = str.substr(1, str.size() - 2);
				for (const string& s : tree.searchByName(name)) cout << s << "\n";
			}
			else {
				cout << tree.searchById(str) << "\n";
			}
		}

		else if (command == "printInorder") printStudentNames(tree.inorder());
		else if (command == "printPreorder") printStudentNames(tree.preorder());
		else if (command == "printPostorder") printStudentNames(tree.postorder());
		else if (command == "printLevelCount") cout << tree.printLevel() << "\n";

		// this block executes when the user inputs an invalid command or one that does not match that of the commands above
		else {
			cout << "unsuccessful\n"; 
		}
	}

	return 0;
}
