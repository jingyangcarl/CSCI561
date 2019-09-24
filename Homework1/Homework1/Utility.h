#pragma once
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <iostream>
using namespace std;

typedef pair<int, int> Location;

typedef struct InputParameter {
public:
	string algorithm = "";
	int height = 0;
	int width = 0;
	Location landingLocation;
	int maxSlope = 0;
	int destinationCount = 0;
	map<Location, vector<Location>> destinations;
	int** map = NULL;

public:
	int GetZ(int i, int j);
	int GetZ(const Location& location);
	int GetSlopeBetween(const Location& location1, const Location& location2);
	float GetDistance(const Location& currentLoc, const Location& destinationLoc);
	int GetManhattanDistance(const Location& currentLoc, const Location& destinationLoc);
} Input;