#pragma once
#include "Utility.h"
#include <vector>
#include <map>

class BFSProcessor {
public:
	BFSProcessor(Input& input);
	void run();
	void BreadFirstSearchRecursionEntrance();
	void BreadFirstSearchRecursion(Location currentLoc, const Location& targetLoc, map<Location, int>& path);
	void BreadFirstSearchNonrecursionEntrance();
	void BreadFirstSearchNonrecursion(const Location targetLoc);
	vector<Location>& GetPath(Location& destination);

private:
	Input &input;
	double count = 0;
};