#pragma once
#include "Utility.h"

class SearchProcessor {
protected:
	virtual void run() = 0;
	virtual void RecursionEntrance() = 0;
	virtual void Recursion(Location currentLoc, const Location& targetLoc, map<Location, int>& path) = 0;
	virtual void NonrecursionEntrance() = 0;
	virtual void Nonrecursion(const Location& targetLoc) = 0;

	Input& input;
};