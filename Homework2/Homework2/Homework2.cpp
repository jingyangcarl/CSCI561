// Homework2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>

#include "Input.h"
#include "Halma.h"
using namespace std;

/*
Description:
This function is the entrance of this project;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
int main() {
	ifstream inputFile("input.txt");
	Input input;

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

		// get game option
		PrepareNextLine(lineBuffer, inputFile);
		input.gameOption = (lineBuffer.str() == "SINGLE") ? 0 : 1;

		// get player
		PrepareNextLine(lineBuffer, inputFile);
		input.player = (lineBuffer.str() == "BLACK") ? 0 : 1;

		// get remaining time
		PrepareNextLine(lineBuffer, inputFile);
		lineBuffer >> input.timeLeft;

		// get board
		input.board = new char* [BOARDSIZE];
		for (int i = 0; i < BOARDSIZE; i++) {
			PrepareNextLine(lineBuffer, inputFile);
			input.board[i] = new char[BOARDSIZE];
			for (int j = 0; j < BOARDSIZE; j++) {
				lineBuffer >> input.board[i][j];
			}
		}
		inputFile.close();

		cout << '\t';
		for (int i = 0; i < BOARDSIZE; i++) {
			cout << i << '\t';
		}
		cout << endl;
		for (int i = 0; i < BOARDSIZE; i++) {
			cout << i << '\t';
			for (int j = 0; j < BOARDSIZE; j++) {
				cout << input.board[i][j] << '\t';
			}
			cout << endl;
		}

		// run
		Halma halma(input);
		halma.run();
		//halma.Output2File();
	}
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
