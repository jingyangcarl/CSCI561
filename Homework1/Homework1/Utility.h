#pragma once
#include <string>
#include <unordered_map>
using namespace std;

typedef struct Coordination {
public:
	int x = 0;
	int y = 0;
} Location;

typedef struct InputParameter {
	string algorithm = "";
	int height = 0;
	int width = 0;
	Location landingLocation;
	int maxSlope = 0;
	int destinationCount = 0;
	unordered_map<int, Location> destinations;
	int** map = NULL;
} Input;