#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include "Utility.h"
#include "InputGenerator.h"
#include "BFSProcessor.h"
using namespace std;


int main() {
	ifstream inputFile("input.txt");
	string line;
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

		// get algorithm;
		PrepareNextLine(lineBuffer, inputFile);
		lineBuffer >> input.algorithm;

		// get height and width;
		PrepareNextLine(lineBuffer, inputFile);
		if (!(lineBuffer >> input.width >> input.height)) return -1;

		// get landing location;
		PrepareNextLine(lineBuffer, inputFile);
		if (!(lineBuffer >> input.landingLocation.first >> input.landingLocation.second)) return -2;

		// get maximum slope for the rover;
		PrepareNextLine(lineBuffer, inputFile);
		if (!(lineBuffer >> input.maxSlope)) return -3;

		// get number of destinations;
		PrepareNextLine(lineBuffer, inputFile);
		if (!(lineBuffer >> input.destinationCount)) return -4;

		// get all destinations' location;
		for (int i = 0; i < input.destinationCount; i++) {
			Location destination;
			PrepareNextLine(lineBuffer, inputFile);
			if (!(lineBuffer >> destination.second >> destination.first)) return -5;
			input.destinations.insert(pair<Location, vector<Location>>(destination, vector<Location>(input.height * input.width)));
		}

		// get all z values on map;
		input.map = new int* [input.height];
		for (int i = 0; i < input.height; i++) {
			PrepareNextLine(lineBuffer, inputFile);
			input.map[i] = new int[input.width];
			for (int j = 0; j < input.width; j++) {
				if (!(lineBuffer >> input.map[i][j])) return -6;
			}
		}
	}
	inputFile.close();

	// generate input;
	//InputGenerator inputGenerator(input);
	//inputGenerator.SetParameter(10, 10, 1, 50, 10);
	//inputGenerator.Generate();
	//inputGenerator.Output();

	// run algorithm;
	clock_t start = clock();
	BFSProcessor processor(input);
	processor.run();
	clock_t end = clock();
	cout << "Running time: " << (end - start) / (double)CLOCKS_PER_SEC << endl;
	
	cout << "Trace: " << endl;
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		for (auto j = (*i).second.begin(); j != (*i).second.end(); j++) {
			cout << "(" << (*j).second << ", " << (*j).first << ")";
		}
		cout << endl;
	}
}