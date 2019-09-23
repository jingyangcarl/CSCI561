#pragma once
#include "Utility.h"

class BFSProcessor {
public:
	BFSProcessor(Input& input);
	void run();

	void BreadFirstSearchEntrance();
	void BreadFirstSearch(const Location& targetLoc);
	void Output();

private:
	Input &input;
	double count = 0;
};