#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include "Utility.h"
#include "InputGenerator.h"
#include "BFSProcessor.h"
#include "UCSProcessor.h"
#include "ASSProcessor.h"
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
		if (!(lineBuffer >> input.landingLocation.second >> input.landingLocation.first)) return -2;

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
		input.landMap = new int* [input.height];
		for (int i = 0; i < input.height; i++) {
			PrepareNextLine(lineBuffer, inputFile);
			input.landMap[i] = new int[input.width];
			for (int j = 0; j < input.width; j++) {
				if (!(lineBuffer >> input.landMap[i][j])) return -6;
			}
		}
	}
	inputFile.close();

	// generate input;
	InputGenerator inputGenerator(input);
	//inputGenerator.SetParameter(15, 15, 1, 50, 10);
	//inputGenerator.Generate();
	//inputGenerator.Output();

	clock_t start, end;

	// run BFS algorithm;
	BFSProcessor bfsProcessor(input);
	start = clock();
	bfsProcessor.Run();
	end = clock();
	cout << "Running time: " << (end - start) / (double)CLOCKS_PER_SEC << endl;
	bfsProcessor.Output();
	bfsProcessor.OutputToFile();

	// run UCS algorithm;
	UCSProcessor ucsProcessor(input);
	start = clock();
	ucsProcessor.Run();
	end = clock();
	cout << "Running time: " << (end - start) / (double)CLOCKS_PER_SEC << endl;
	ucsProcessor.Output();
	ucsProcessor.OutputToFile();

	// run ASS algorithm;
	ASSProcessor assProcessor(input);
	start = clock();
	assProcessor.Run();
	end = clock();
	cout << "Running time: " << (end - start) / (double)CLOCKS_PER_SEC << endl;
	assProcessor.Output();
	assProcessor.Output();
}