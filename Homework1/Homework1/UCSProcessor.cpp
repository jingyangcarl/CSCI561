#include "UCSProcessor.h"

/*
Description:
This function is a constructor;
Input:
@ Input& input: a defined input structure;
Output:
@ UCSProcessor returnValue: a UCSProcessor;
*/
UCSProcessor::UCSProcessor(Input& input) :
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
void UCSProcessor::Run() {
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
void UCSProcessor::Output() {
	cout << "UCS Trace: " << endl;
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
void UCSProcessor::OutputToFile() {
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
void UCSProcessor::SearchEntrance() {
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		(*i).second.clear();
		Search((*i).first);
	}
}

/*
Description:
This function is used to perform Uniform Cost search algorithm to find a path from landing location to target location;
Input:
@ const Location& targetLoc: a target location;
Output:
@ void returnValue: void;
*/
void UCSProcessor::Search(const Location& targetLoc) {

	priority_queue<pair<int, Location>> UCS;
	set<Location> UCSVisited;
	set<Location> UCSVisiting;
	map<Location, Location> trace;

	UCS.push(pair<int, Location>(0, input.landingLocation));
	while (!UCS.empty()) {
		// get the top node, the current priority queue is a max heap, use negative cost to convert it to a min heap;
		int currentCost = UCS.top().first;
		Location currentLoc = UCS.top().second;
		UCSVisited.insert(currentLoc);
		UCS.pop();

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
					// get the next cost, 
					// if the next location is on North, South, West, and East, the cost should be 10, 
					// if the next location is on NW, NE, SW, SE, the cost should be 14;
					// otherwise, the cost should be infinite large;
					int nextCost = currentCost + ((abs(i) + abs(j) == 1) ? -10 : (abs(i) + abs(j) == 2) ? -14 : -INT_MAX);
					// check if the node is visited
					if (UCSVisited.find(nextLoc) != UCSVisited.end()) continue;
					// check if the node is already in the set to be visiting
					if (UCSVisiting.find(nextLoc) != UCSVisiting.end()) continue;
					// check if the ndoe is reachable
					if (input.GetSlopeBetween(currentLoc, nextLoc) <= input.maxSlope) {
						// remember child-parent order for tracing back
						trace.insert(pair<Location, Location>(nextLoc, currentLoc));
						// push node
						UCS.push(pair<int, Location>(nextCost, nextLoc));
						// remember node to be visited;
						UCSVisiting.insert(nextLoc);
					}
				}
			}
		}
	}
}
