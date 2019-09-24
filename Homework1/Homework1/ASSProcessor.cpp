#include "ASSProcessor.h"

ASSProcessor::ASSProcessor(Input& input) :
	input(input) {
}

void ASSProcessor::Run() {
	SearchEntrance();
}

void ASSProcessor::SearchEntrance() {
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		(*i).second.clear();
		Search((*i).first);
	}
}

void ASSProcessor::Search(const Location& targetLoc) {

	priority_queue<pair<int, Location>> ASS;
	set<Location> ASSVisited;
	set<Location> ASSVisiting;
	map<Location, Location> trace;

	int predictCost = input.GetDistance(input.landingLocation, targetLoc) * -10;
	ASS.push(pair<int, Location>(predictCost, input.landingLocation));
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
					int predictCost = input.GetDistance(currentLoc, targetLoc) * -10;
					int nextCost = predictCost - ((abs(i) + abs(j) == 1) ? -10 : (abs(i) + abs(j) == 2) ? -14 : -INT_MAX);
					// check if the node is visited
					if (ASSVisited.find(nextLoc) != ASSVisited.end()) continue;
					// check if the node is already in the set to be visiting
					if (ASSVisiting.find(nextLoc) != ASSVisiting.end()) continue;
					// check if the ndoe is reachable
					if (input.GetSlopeBetween(currentLoc, nextLoc) <= input.maxSlope) {
						// remember child-parent order for tracing back
						trace.insert(pair<Location, Location>(nextLoc, currentLoc));
						// push node
						ASS.push(pair<int, Location>(nextCost, nextLoc));
						// remember node to be visited;
						ASSVisiting.insert(nextLoc);
					}
				}
			}
		}
	}
}

void ASSProcessor::Output() {
	cout << "ASS Trace: " << endl;
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		for (auto j = (*i).second.rbegin(); j != (*i).second.rend(); j++) {
			cout << "(" << (*j).second << ", " << (*j).first << ")";
		}
		cout << endl;
	}
}
