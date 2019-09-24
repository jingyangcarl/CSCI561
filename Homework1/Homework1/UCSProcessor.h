#pragma once
#include "Utility.h"
#include "SearchProcessor.h"

class UCSProcessor : SearchProcessor {
public:
	UCSProcessor(Input& input);
	void Run();
	void Output();

private:
	void SearchEntrance();
	void Search(const Location& targetLoc);

private:
	Input& input;
};