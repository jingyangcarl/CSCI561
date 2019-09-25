#pragma once
#include "Utility.h"
#include "SearchProcessor.h"

class ASSProcessor : SearchProcessor {
public:
	ASSProcessor(Input& input);
	void Run();
	void Output();
	void OutputToFile();

private:
	void SearchEntrance();
	void Search(const Location& targetLoc);

private:
	Input& input;
};