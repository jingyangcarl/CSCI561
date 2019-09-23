#pragma once
#include "Utility.h"

class UCSProcessor {
public:
	UCSProcessor(Input& input);
	void run();

	void UniformCostSearchNonrecursionEntrance();
	void UniformCostSearchNonrecursion(const Location targetLoc);

private:
	Input& input;
};