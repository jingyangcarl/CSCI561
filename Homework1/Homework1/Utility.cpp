#include "Utility.h"

/*
Description:
This function is used to get z value for a given location;
Input:
@ int i: row number;
@ int j: column number;
Output:
@ int returnValue: z value at i, j;
*/
int InputParameter::GetZ(int i, int j) {
	if (i < 0 || i >= height) return -INT_MAX;
	if (j < 0 || j >= width) return -INT_MAX;
	return landMap[i][j];
}

/*
Description:
This function is used to get z value for a given location;
Input:
@ const Location& location: a given location;
Output:
@ int returnValue: z value at given location;
*/
int InputParameter::GetZ(const Location& location) {
	return GetZ(location.first, location.second);
}

/*
Description:
This function is used to get z difference between two locations, which is used to compare with max slope;
Input:
@ const Location& location1: a location;
@ const Location& location2: a location;
Output:
@ int returnValue: z difference between location1 and location2;
*/
int InputParameter::GetSlopeBetween(const Location& location1, const Location& location2) {
	return abs(GetZ(location1) - GetZ(location2));
}

/*
Description:
This function is used to get Euclid distance between two locations;
Input:
@ const Location& location1: a location;
@ const Location& location2: a location;
Output:
@ int returnValue: Euclid distance between location1 and location2;
*/
float InputParameter::GetDistance(const Location& location1, const Location& location2) {
	int x1 = location1.first;
	int y1 = location1.second;
	int z1 = GetZ(location1);
	int x2 = location2.first;
	int y2 = location2.second;
	int z2 = GetZ(location2);
	return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

/*
Description:
This function is used to get Manhattan distance between two locations;
Input:
@ const Location& location1: a location;
@ const Location& location2: a location;
Output:
@ int returnValue: Manhattan distance between location1 and location2;
*/
int InputParameter::GetManhattanDistance(const Location& currentLoc, const Location& destinationLoc) {
	int deltaX = abs(currentLoc.first - destinationLoc.first);
	int deltaY = abs(currentLoc.second - destinationLoc.second);
	int deltaZ = abs(GetZ(currentLoc) - GetZ(destinationLoc));
	return deltaX + deltaY + deltaZ;
}
