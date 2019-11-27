// Homework3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>

#include "Input.h"
#include "KnowledgeBase.h"

using namespace std;

int main() {

	ifstream inputFile("input2.txt");
	InputParameter input;

	if (inputFile.is_open()) {
		string line;
		istringstream lineBuffer;

		/*
		Description:
		This function is used to read input file line by lin to line buffer;
		Input:
		@ istringstream& lineBuffer: a line buffer;
		@ ifstream& inputFile: an input file;
		Output:
		@ auto returnValue: void;
		*/
		auto PrepareNextLine = [](istringstream& lineBuffer, ifstream& inputFile) {
			string line;
			getline(inputFile, line);
			lineBuffer.clear();
			lineBuffer.str(line);
		};

		// get number of queries
		PrepareNextLine(lineBuffer, inputFile);
		input.querySize = atoi(lineBuffer.str().c_str());

		// get all queries
		for (int i = 0; i < input.querySize; i++) {
			PrepareNextLine(lineBuffer, inputFile);
			input.queries.push_back(lineBuffer.str());
		}
		
		// get number of sentences in knowledges base
		PrepareNextLine(lineBuffer, inputFile);
		input.sentenceSize = atoi(lineBuffer.str().c_str());
		
		// get all sentences in knowledges base
		for (int i = 0; i < input.sentenceSize; i++) {
			PrepareNextLine(lineBuffer, inputFile);
			input.sentences.push_back(lineBuffer.str());
		}
	}
	inputFile.close();
	input.Print();

	// Tell Knowledge Base
	KnowledgeBase knowledgeBase;
	for (auto& sentence : input.sentences) {
		knowledgeBase.Tell(sentence);
	}

	string predicate_str = "Alert(Bob, NSAIDs)";
	cout << knowledgeBase.Ask(predicate_str) << endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
