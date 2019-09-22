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
