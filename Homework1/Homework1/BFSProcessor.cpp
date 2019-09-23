#include "BFSProcessor.h"
#include <iostream>
#include <queue>
#include <set>

BFSProcessor::BFSProcessor(Input& input) :
	input(input) {
}

void BFSProcessor::run() {
	BreadFirstSearchNonrecursionEntrance();
}

void BFSProcessor::BreadFirstSearchRecursionEntrance() {

	map<Location, int> path;
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		// prepare path;
		path.clear();
		path.insert(pair<Location, int>(input.landingLocation, path.size() + 1));
		BreadFirstSearchRecursion(input.landingLocation, (*i).first, path);
	}
}

void BFSProcessor::BreadFirstSearchRecursion(Location currentLoc, const Location& targetLoc, map<Location, int>& path) {

	// pruning
	if (path.size() >= (*(input.destinations.find(targetLoc))).second.size()) return;

	// count
	count++;

	if (currentLoc == targetLoc) {
		// found the path to destination;
		map<int, Location> transposePath;
		for (const auto& i : path) {
			transposePath.insert(pair<int, Location>(i.second, i.first));
		}

		vector<Location>& currentPath = (*(input.destinations.find(targetLoc))).second;
		if (transposePath.size() < currentPath.size()) {
			currentPath.clear();
			for (const auto& i : transposePath) {
				currentPath.push_back(i.second);
				cout << "(" << (i.second).first << ", " << (i.second).second << ")";
			}
			cout << endl;
		}
	}
	else {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				Location nextLocation(currentLoc.first + i, currentLoc.second + j);
				if (nextLocation == currentLoc) continue;
				if (path.find(nextLocation) != path.end()) continue;
				if (input.GetSlopeBetween(currentLoc, nextLocation) <= input.maxSlope) {
					path.insert(pair<Location, int>(nextLocation, path.size() + 1));
					BreadFirstSearchRecursion(nextLocation, targetLoc, path);
					path.erase(nextLocation);
				}
			}
		}
	}
}

void BFSProcessor::BreadFirstSearchNonrecursionEntrance() {
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		(*i).second.clear();
		BreadFirstSearchNonrecursion((*i).first);
	}
}

void BFSProcessor::BreadFirstSearchNonrecursion(const Location targetLoc) {
	queue<Location> BFS;
	set<Location> BFSVisiting;
	set<Location> BFSVisited;
	map<Location, Location> trace;

	BFS.push(input.landingLocation);
	while (!BFS.empty()) {
		Location currentLoc = BFS.front();
		BFSVisited.insert(currentLoc);
		BFS.pop();
		if (currentLoc == targetLoc) {
			// find the solution
			Location traceBackLocation(currentLoc);
			while (traceBackLocation != input.landingLocation) {
				input.destinations.at(targetLoc).push_back(traceBackLocation);
				traceBackLocation = (*trace.find(traceBackLocation)).second;
			}
			input.destinations.at(targetLoc).push_back(traceBackLocation);
		}
		else {
			for (int i = -1; i < 2; i++) {
				for (int j = -1; j < 2; j++) {
					if (currentLoc.first + i >= input.height || currentLoc.first + i < 0) continue;
					if (currentLoc.second + j >= input.width || currentLoc.second + j < 0) continue;
					Location nextLoc(currentLoc.first + i, currentLoc.second + j);
					if (BFSVisited.find(nextLoc) != BFSVisited.end()) continue;
					if (BFSVisiting.find(nextLoc) != BFSVisiting.end()) continue;
					if (input.GetSlopeBetween(currentLoc, nextLoc) <= input.maxSlope) {
						trace.insert(pair<Location, Location>(nextLoc, currentLoc));
						BFS.push(nextLoc);
						BFSVisiting.insert(nextLoc);
					}
				}
			}
		}
	}
}

vector<Location>& BFSProcessor::GetPath(Location& destination) {
	if (input.destinations.find(destination) != input.destinations.end()) {
		return (*(input.destinations.find(destination))).second;
	}
}
