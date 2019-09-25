#include "BFSProcessor.h"

/*
Description:
This function is a constructor;
Input:
@ Input& input: a defined input structure;
Output:
@ BFSProcessor returnValue: a BFSProcessor;
*/
BFSProcessor::BFSProcessor(Input& input) :
	input(input) {
}

/*
Description:
This function is used to start the processor;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void BFSProcessor::Run() {
	SearchEntrance();
}

/*
Description:
This function is used to output the path;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void BFSProcessor::Output() {
	cout << "BFS Trace: " << endl;
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		for (auto j = (*i).second.rbegin(); j != (*i).second.rend(); j++) {
			cout << "(" << (*j).second << ", " << (*j).first << ")";
		}
		cout << endl;
	}
}

/*
Description:
This function is used to output the path to an output file;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void BFSProcessor::OutputToFile() {
	ofstream output("output.txt");
	if (output.is_open()) {
		for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
			if (!(*i).second.empty()) {
				for (auto j = (*i).second.rbegin(); j != (*i).second.rend(); j++) {
					output << (*j).second << "," << (*j).first << " ";
				}
				output << endl;
			}
			else {
				output << "FAIL" << endl;
			}
		}
	}
	output.close();
}

/*
Description:
This function is used to loop through all the desitinations;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void BFSProcessor::SearchEntrance() {
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		(*i).second.clear();
		Search((*i).first);
	}
}

/*
Description:
This function is used to perform Breadth First search algorithm to find a path from landing location to target location;
Input:
@ const Location& targetLoc: a target location;
Output:
@ void returnValue: void;
*/
void BFSProcessor::Search(const Location& targetLoc) {
	queue<Location> BFS;
	set<Location> BFSVisited;
	set<Location> BFSVisiting;
	map<Location, Location> trace;

	BFS.push(input.landingLocation);
	while (!BFS.empty()) {
		// get the top node;
		Location currentLoc = BFS.front();
		BFSVisited.insert(currentLoc);
		BFS.pop();

		// found the solution
		if (currentLoc == targetLoc) {
			// traceback
			Location traceBackLocation(currentLoc);
			while (traceBackLocation != input.landingLocation) {
				// push the current tracing back location;
				input.destinations.at(targetLoc).push_back(traceBackLocation);
				// look for its parent;
				traceBackLocation = (*trace.find(traceBackLocation)).second;
			}
			// add landing location;
			input.destinations.at(targetLoc).push_back(traceBackLocation);
		}
		else {
			// for eight neighbors
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					// check if the location is valid on map
					if (currentLoc.first + i >= input.height || currentLoc.first + i < 0) continue;
					if (currentLoc.second + j >= input.width || currentLoc.second + j < 0) continue;
					// get the next location
					Location nextLoc(currentLoc.first + i, currentLoc.second + j);
					// check if the node is visited
					if (BFSVisited.find(nextLoc) != BFSVisited.end()) continue;
					// check if the node is already in the set to be visiting
					if (BFSVisiting.find(nextLoc) != BFSVisiting.end()) continue;
					// check if the node is reachable
					if (input.GetSlopeBetween(currentLoc, nextLoc) <= input.maxSlope) {
						// remember child-parent order for tracing back
						trace.insert(pair<Location, Location>(nextLoc, currentLoc));
						// push node
						BFS.push(nextLoc);
						// remember node to be visited;
						BFSVisiting.insert(nextLoc);
					}
				}
			}
		}
	}
}