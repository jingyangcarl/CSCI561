#pragma once
#include "Utility.h"
#include "SearchProcessor.h"

class BFSProcessor : SearchProcessor {
public:
	BFSProcessor(Input& input);
	void Run();
	void Output();

private:
	void SearchEntrance();
	void Search(const Location& targetLoc);

private:
	Input &input;
	double count = 0;
};