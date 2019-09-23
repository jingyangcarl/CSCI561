#pragma once
#include "Utility.h"

class ASSProcessor {
public:
	ASSProcessor(Input& input);
	void run();

	void AStarSearchNonrecursionEntrance();
	void AStarSearchNonrecursion(const Location targetLoc);

private:
	Input& input;
};