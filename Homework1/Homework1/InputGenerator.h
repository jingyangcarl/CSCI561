#pragma once
#include "Utility.h"
#include <random>
#include <iostream>
#include <time.h>
#include <time.h>

class InputGenerator {
public:
	InputGenerator(Input& input);

	void SetParameter(int width, int height, int destinations, int zMean, int zStddev);
	void Generate();
	void Output();
	void OutputToFile();

private:
	int width = 0;
	int height = 0;
	int destinations = 0;
	float zMean = 0.0;
	float zStddev = 0.0;
	Input& input;
};