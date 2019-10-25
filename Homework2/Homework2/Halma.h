#pragma once
#include <ctime>
#include "Input.h"
#include <math.h>
#include <vector>
#include <map>
using namespace std;

class Halma {
public:
	Halma(Input& input);
	void run();

protected:
	float Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing = true);
	float Evaluation(bool player);
	float EuclideanDistance(float x1, float y1, float x2, float y2);
	int Winner();
	map<pair<int, int>, vector<pair<int, int>>>& GetNextMoves(bool player);
	void GetNextMoves(pair<int, int> from, vector<pair<int, int>>& moves);

private:
	Input& input;

	int plyDepth;

	// vector to save goal locations;
	vector<pair<int, int>> blackGoal;
	vector<pair<int, int>> whiteGoal;

};

