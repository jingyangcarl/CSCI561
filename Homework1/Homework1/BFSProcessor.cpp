#include "BFSProcessor.h"
#include <iostream>

BFSProcessor::BFSProcessor(Input& input) :
	input(input) {
}

void BFSProcessor::run() {
	map<Location, int> path;
	path.insert(pair<Location, int>(input.landingLocation, path.size() + 1));
	BreadFirstSearch(input.landingLocation, path);
}

void BFSProcessor::BreadFirstSearch(Location currentLocation, map<Location, int>& path) {
	if (input.destinations.find(currentLocation) != input.destinations.end()) {
		// found the path to destination;
		map<int, Location> transposePath;
		for (const auto& i : path) {
			transposePath.insert(pair<int, Location>(i.second, i.first));
		}

		//for (const auto& i : transposePath) {
		//	cout << "(" << i.second.first << ", " << i.second.second << ") -> ";
		//}
		//cout << endl;
		vector<Location>& currentPath = (*(input.destinations.find(currentLocation))).second;
		if (transposePath.size() < currentPath.size()) {
			currentPath.clear();
			for (const auto& i : transposePath) {
				currentPath.push_back(i.second);
			}
		}

	}
	else {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				Location nextLocation(currentLocation.first + i, currentLocation.second + j);
				if (nextLocation == currentLocation) continue;
				if (path.find(nextLocation) != path.end()) continue;
				if (input.GetSlopeBetween(currentLocation, nextLocation) < input.maxSlope) {
					path.insert(pair<Location, int>(nextLocation, path.size() + 1));
					BreadFirstSearch(nextLocation, path);
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
