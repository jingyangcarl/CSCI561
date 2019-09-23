#pragma once
#include "Utility.h"

class ASSProcessor {
public:
	ASSProcessor(Input& input);
	void run();

	void AStarSearchEntrance();
	void AStarSearch(const Location targetLoc);
	void Output();

private:
	Input& input;
};