#include "Utility.h"

int InputParameter::GetZ(int i, int j) {
	if (i < 0 || i >= height) return -INT_MAX;
	if (j < 0 || j >= width) return -INT_MAX;
	return map[i][j];
}

int InputParameter::GetZ(const Location& location) {
	return GetZ(location.first, location.second);
}

int InputParameter::GetSlopeBetween(const Location& location1, const Location& location2) {
	return abs(GetZ(location1) - GetZ(location2));
}

float InputParameter::GetDistance(const Location& currentLoc, const Location& destinationLoc) {
	int x1 = currentLoc.first;
	int y1 = currentLoc.second;
	int z1 = GetZ(currentLoc);
	int x2 = destinationLoc.first;
	int y2 = destinationLoc.second;
	int z2 = GetZ(destinationLoc);
	return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

int InputParameter::GetManhattanDistance(const Location& currentLoc, const Location& destinationLoc) {
	int deltaX = abs(currentLoc.first - destinationLoc.first);
	int deltaY = abs(currentLoc.second - destinationLoc.second);
	int deltaZ = abs(GetZ(currentLoc) - GetZ(destinationLoc));
	return deltaX + deltaY + deltaZ;
}
