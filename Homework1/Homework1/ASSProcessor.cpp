#include "ASSProcessor.h"

/*
Description:
This function is a constructor;
Input:
@ Input& input: a defined input structure;
Output:
@ ASSProcessor returnValue: a ASSProcessor;
*/
ASSProcessor::ASSProcessor(Input& input) :
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
void ASSProcessor::Run() {
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
void ASSProcessor::Output() {
	cout << "ASS Trace: " << endl;
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
void ASSProcessor::OutputToFile() {
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
void ASSProcessor::SearchEntrance() {
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		(*i).second.clear();
		Search((*i).first);
	}
}

/*
Description:
This function is used to perform A* search algorithm to find a path from landing location to target location;
Input:
@ const Location& targetLoc: a target location;
Output:
@ void returnValue: void;
*/
void ASSProcessor::Search(const Location& targetLoc) {

	priority_queue<pair<int, Location>> ASS;
	// used to save visited node and visiting node;
	set<Location> ASSVisited;
	map<Location, int> ASSVisiting;
	// used to remember parent-child order for tracing back
	map<Location, Location> trace;

	ASS.push(pair<int, Location>(0, input.landingLocation));
	while (!ASS.empty()) {
		// get the top node, the current priority queue is a max heap, use negative cost to convert it to a min heap;
		int currentCost = ASS.top().first;
		Location currentLoc = ASS.top().second;
		ASSVisited.insert(currentLoc);
		ASS.pop();

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
			return;
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
					// check if the node is rechable;
					if (input.GetSlopeBetween(currentLoc, nextLoc) > input.maxSlope) continue;
					// check if the node is visited
					if (ASSVisited.find(nextLoc) != ASSVisited.end()) continue;
					// get the next cost, 
					// if the next location is on North, South, West, and East, the cost should be 10, 
					// if the next location is on NW, NE, SW, SE, the cost should be 14;
					// otherwise, the cost should be infinite large;
					int nextHorizontalCost = -((abs(i) + abs(j) == 1) ? 10 : (abs(i) + abs(j) == 2) ? 14 : INT_MAX);
					int nextVerticalCost = -input.GetSlopeBetween(currentLoc, nextLoc);
					int nextCost = currentCost + nextHorizontalCost + nextVerticalCost;
					// check if the node is already in the set to be visiting, if there is update the cost
					if (ASSVisiting.find(nextLoc) != ASSVisiting.end()) {
						if (nextCost > (*ASSVisiting.find(nextLoc)).second) {
							(*trace.find(nextLoc)).second = currentLoc;
							ASS.push(pair<int, Location>(nextCost, nextLoc));
						}
						continue;
					}
					// for valid nodes
					// remember child-parent order for tracing back
					trace.insert(pair<Location, Location>(nextLoc, currentLoc));
					// push node
					ASS.push(pair<int, Location>(nextCost, nextLoc));
					// remember node to be visited;
					ASSVisiting.insert(pair<Location, int>(nextLoc, nextCost));
				}
			}
		}
	}
}