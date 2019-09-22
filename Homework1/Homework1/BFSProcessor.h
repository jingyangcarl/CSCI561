#pragma once
#include "Utility.h"
#include <vector>
#include <map>

class BFSProcessor {
public:
	BFSProcessor(Input& input);
	void run();
	void BreadFirstSearch(Location currentLoc, map<Location, int>& path);
	vector<Location>& GetPath(Location& destination);

private:
	Input &input;
};