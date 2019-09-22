#pragma once
#include "Utility.h"
#include <vector>

class BFSProcessor {
public:
	BFSProcessor(Input& input);
	void run();
	void BreadFirstSearch(Location currentLoc, std::vector<Location> path);

private:
	Input &input;
};