#include "BFSProcessor.h"
#include <iostream>

BFSProcessor::BFSProcessor(Input& input) :
	input(input) {
}

void BFSProcessor::run() {
	map<Location, int> path;

	//path.insert(pair<Location, int>(input.landingLocation, path.size() + 1));
	//BreadFirstSearch(input.landingLocation, path);
	//cout << "count: " << count << endl;

	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		path.clear();
		path.insert(pair<Location, int>(input.landingLocation, path.size() + 1));
		BreadFirstSearch((*i).first, input.landingLocation, path);
	}
	cout << "count: " << count << endl;
}

void BFSProcessor::BreadFirstSearch(Location currentLoc, map<Location, int>& path) {
	// pruning

	// count
	count++;

	if (input.destinations.find(currentLoc) != input.destinations.end()) {
		// found the path to destination;
		map<int, Location> transposePath;
		for (const auto& i : path) {
			transposePath.insert(pair<int, Location>(i.second, i.first));
		}

		vector<Location>& currentPath = (*(input.destinations.find(currentLoc))).second;
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
				if (input.GetSlopeBetween(currentLoc, nextLocation) < input.maxSlope) {
					path.insert(pair<Location, int>(nextLocation, path.size() + 1));
					BreadFirstSearch(nextLocation, path);
					path.erase(nextLocation);
				}
			}
		}
	}
}

void BFSProcessor::BreadFirstSearch(const Location& targetLoc, Location currentLoc, map<Location, int>& path) {
	// pruning
	if (path.size() > (*(input.destinations.find(targetLoc))).second.size()) return;

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
				if (input.GetSlopeBetween(currentLoc, nextLocation) < input.maxSlope) {
					path.insert(pair<Location, int>(nextLocation, path.size() + 1));
					BreadFirstSearch(targetLoc, nextLocation, path);
					path.erase(nextLocation);
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
