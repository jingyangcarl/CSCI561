#pragma once
#include <ctime>
#include "Input.h"
#include <math.h>
#include <vector>
using namespace std;

class Halma {
public:
	Halma(Input& input);
	void run();

protected:
	float Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing = true);
	float Evaluation();
	float EuclideanDistance(float x1, float y1, float x2, float y2);

private:
	Input& input;
	int plyDepth;

	vector<pair<int, int>> blackGoal;
	vector<pair<int, int>> whiteGoal;

};

