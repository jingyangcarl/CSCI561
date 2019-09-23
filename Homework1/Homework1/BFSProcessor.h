#pragma once
#include "Utility.h"
#include <vector>
#include <map>

class BFSProcessor {
public:
	BFSProcessor(Input& input);
	void run();

	void BreadFirstSearchNonrecursionEntrance();
	void BreadFirstSearchNonrecursion(const Location& targetLoc);

private:
	Input &input;
	double count = 0;
};