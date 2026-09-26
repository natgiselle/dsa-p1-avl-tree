


// // Name: Natalie Ortiz
// // UFID: 62121115

// #include "catch/catch_amalgamated.cpp"
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <vector>
// #include <ctime> // for true randomization
// #include <cstdlib>
// #include <algorithm>
// #include "../src/avl_tree.h"

// using namespace std;


// // ID: makes unique letters-only name from 8-digit ID
// static string getNameFromId(const string& id) {
// 	string name;
// 	for (char c : id) {
// 		name += char('a' + (c-'0')); // makes 8 digit ID unique letters only
// 	}
// 	return name;
// }


// /** TEST CASE 1: 5 commands */
// TEST_CASE("Invalid commands", "[invalid]"){
// 	SECTION("commands") {
// 		AVLTree tree;
// 		REQUIRE_FALSE(tree.insert("Gise11e", "43599999"));
// 		REQUIRE_FALSE(tree.insert("N9talie", "12345678"));
// 		REQUIRE_FALSE(tree.insert("Nat@lie", "12345678"));
// 		REQUIRE_FALSE(tree.insert("Natalie", "1234567"));
// 		REQUIRE_FALSE(tree.insert("Natalie", "123456789"));
// 		REQUIRE_FALSE(tree.insert("Natalie", "1234567A"));
// 		REQUIRE_FALSE(tree.insert("Natalie", "12345678b"));
// 		REQUIRE(tree.insert("Natalie", "12345678")); // the only successful one

// 		REQUIRE(tree.inorder().size() == 1);
// 	}
// }

// // TEST CASE 2: rotations and insertion ACTUAL VS EXPECTED

// TEST_CASE("Insert Test with all 4 rotation cases", "[rotation]"){
// 	vector<string> expectedPre = {"Thirty", "Twenty", "Forty"};
// 	vector<string> expectedIn = {"Twenty", "Thirty", "Forty"};

// 	SECTION("LL (R rotation)") {
// 		AVLTree tree;
// 		REQUIRE(tree.insert("Forty","40000000"));
// 		REQUIRE(tree.insert("Thirty","30000000"));
// 		REQUIRE(tree.insert("Twenty","20000000"));
// 		REQUIRE(tree.preorder() == expectedPre);
// 		REQUIRE(tree.inorder() == expectedIn);
// 	}
	
// 	SECTION("RR (L rotation)") {
// 		AVLTree tree;
// 		REQUIRE(tree.insert("Twenty","20000000"));
// 		REQUIRE(tree.insert("Thirty","30000000"));
// 		REQUIRE(tree.insert("Forty","40000000"));
// 		REQUIRE(tree.preorder() == expectedPre);
// 		REQUIRE(tree.inorder() == expectedIn);
// 	}

// 	SECTION("LR (LR doubled rotation)") {
// 		AVLTree tree;
// 		REQUIRE(tree.insert("Forty","40000000"));
// 		REQUIRE(tree.insert("Twenty","20000000"));
// 		REQUIRE(tree.insert("Thirty","30000000"));
// 		REQUIRE(tree.preorder() == expectedPre);
// 		REQUIRE(tree.inorder() == expectedIn);
// 	}

// 	SECTION("RL (RL doubled rotation)") {
// 		AVLTree tree;
// 		REQUIRE(tree.insert("Twenty","20000000"));
// 		REQUIRE(tree.insert("Forty","40000000"));
// 		REQUIRE(tree.insert("Thirty","30000000"));
// 		REQUIRE(tree.preorder() == expectedPre);
// 		REQUIRE(tree.inorder() == expectedIn);
// 	}
// }

// // TEST CASE 3: NODE REMOVAL, INSERTION AND VERIFICATION 
// TEST_CASE("Insert 100 nodes, remove 10 random, verify it inorder", "[scaling]"){
// 		// MyAVLTree tree;   // Create a Tree object
// 		// tree.insert(3);
// 		// tree.insert(2);
// 		// tree.insert(1);
// 		// std::vector<int> actualOutput = tree.inorder();
// 		// std::vector<int> expectedOutput = {1, 2, 3};
// 		// REQUIRE(expectedOutput.size() == actualOutput.size());
// 		// REQUIRE(actualOutput == expectedOutput);
// 	AVLTree tree;
// 	vector<string> IDs;
// 	vector<string> expectedOutput;
// 	vector<string> actualOutput;

// 	unsigned seed = static_cast<unsigned>(time(nullptr));
// 	srand(seed);
// 	INFO("randomized seed = " << seed);

// 	// inserts 100 unique IDs of 8-digit length
// 	while (IDs.size() < 100) {
// 		string id = to_string(10000000 + rand() % 90000000);
// 		if (count(IDs.begin(), IDs.end(), id) == 0 ) {
// 			IDs.push_back(id);
// 			expectedOutput.push_back(getNameFromId(id));
// 			REQUIRE(tree.insert(getNameFromId(id), id));
// 		}
// 	}


// 	// verifies the added nodes
// 	actualOutput = tree.inorder();
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	sort(expectedOutput.begin(), expectedOutput.end()); // using the include <algorithm> header to make it easier rather than implementing my own func for testing
// 	REQUIRE(expectedOutput == actualOutput);

// 	// remove 10 nodes out of random and ensures each removal succeeds
// 	vector<string> removedNames;
// 	for (int i = 0; i < 10; i++) {
// 		int pick = static_cast<int>(rand()) % IDs.size();
// 		string id = IDs[pick];
// 		string name = getNameFromId(id);
		
// 		REQUIRE(tree.remove(id));

// 		IDs.erase(IDs.begin() + pick);
		
// 		expectedOutput.erase(find(expectedOutput.begin(), expectedOutput.end(), name));
// 		removedNames.push_back(name);
// 	}

// 	// verification for if the next 90 actually match our desired output
// 	actualOutput = tree.inorder();
// 	REQUIRE(actualOutput.size() == 90);
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(expectedOutput == actualOutput);


// 	// this makes sure that all the names we removed are truly removed so that means they CANNOT be appearing within the actual output anymore
// 	for (const string& removed : removedNames) {
// 		REQUIRE(find(actualOutput.begin(), actualOutput.end(), removed) == actualOutput.end());
// 	}
// }

// // TEST CASE 4: THREE DELETION CASES

// TEST_CASE("Deletion cases", "[delete]") {
// 	AVLTree tree;

// 	tree.insert("Bulbasaur", "20000000");
// 	tree.insert("Azurill", "10000000");
// 	tree.insert("Dwebble", "40000000");
// 	tree.insert("Chikorita", "30000000");
// 	tree.insert("Espeon", "50000000");

// 	SECTION("no children") {
// 		REQUIRE(tree.remove("10000000"));
// 		REQUIRE(tree.inorder() == vector<string>{"Bulbasaur", "Chikorita", "Dwebble", "Espeon"});
// 	}
	
// 	SECTION("1 child") {
// 		REQUIRE(tree.remove("50000000"));
// 		REQUIRE(tree.remove("40000000"));
// 		REQUIRE(tree.inorder() == vector<string>{"Azurill", "Bulbasaur", "Chikorita"});
// 	}
// 	SECTION("2 children") {
// 		REQUIRE(tree.remove("40000000"));
// 		REQUIRE(tree.preorder() == vector<string>{"Bulbasaur", "Azurill", "Espeon", "Chikorita"});
// 	}
// }

// // TEST CASE 5: TRYING OUT THE EDGE CASES 
// TEST_CASE("Edge cases", "[edge]") {
// 	AVLTree tree;

// 	REQUIRE_FALSE(tree.remove("12345678")); // removes an empty tree
// 	REQUIRE(tree.printLevel() == 0); // 0 LEVELS for empty tree 
// 	REQUIRE(tree.insert("Maluma", "12345678")); 
// 	REQUIRE_FALSE(tree.insert("Shakira", "12345678")); // ID duplicate is not accepted (NO two students should have the same ID )
// 	REQUIRE_FALSE(tree.removeInorder(5)); // N is past the end of tree
// 	REQUIRE(tree.searchById("99999999") == "unsuccessful"); // ID is not in the tree
// }