#pragma once
#include "Utility.h"

class UCSProcessor {
public:
	UCSProcessor(Input& input);
	void run();

	void UniformCostSearchEntrance();
	void UniformCostSearch(const Location targetLoc);
	void Output();

private:
	Input& input;
};