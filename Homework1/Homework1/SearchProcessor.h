#pragma once
#include "Utility.h"

class SearchProcessor {
protected:
	virtual void Run() = 0;
	virtual void SearchEntrance() = 0;
	virtual void Search(const Location& targetLoc) = 0;
	virtual void Output() = 0;
	virtual void OutputToFile() = 0;
};