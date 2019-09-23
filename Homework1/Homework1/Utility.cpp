#include "Utility.h"

int InputParameter::GetZ(int i, int j) {
	if (i < 0 || i >= height) return -INT_MAX;
	if (j < 0 || j >= width) return -INT_MAX;
	return map[i][j];
}

int InputParameter::GetZ(Location& location) {
	return GetZ(location.first, location.second);
}

int InputParameter::GetSlopeBetween(Location& location1, Location& location2) {
	return abs(GetZ(location1) - GetZ(location2));
}

float InputParameter::GetDistance(const Location& currentLoc, const Location& destinationLoc) {
	int x1 = currentLoc.first;
	int y1 = currentLoc.second;
	int x2 = destinationLoc.first;
	int y2 = destinationLoc.second;
	return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
