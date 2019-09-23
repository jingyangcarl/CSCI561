#pragma once
#include "Utility.h"
#include <vector>
#include <map>

class BFSProcessor {
public:
	BFSProcessor(Input& input);
	void run();

	void BreadFirstSearchEntrance();
	void BreadFirstSearch(const Location& targetLoc);

private:
	Input &input;
	double count = 0;
};