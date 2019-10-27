#pragma once
#include <ctime>
#include "Input.h"
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct MinimaxReturn {
	float value;
	pair<int, int> from;
	pair<int, int> to;
};

class Halma {
public:
	Halma(Input& input);
	void run();
	void Output2File();

protected:
	MinimaxReturn Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing, float alpha, float beta);
	map<pair<int, int>, vector<pair<int, int>>>& GetNextMoves(bool player);
	void GetNextMoves(pair<int, int> from, vector<pair<int, int>>& moves);
	void GetTrace(pair<int, int> from, pair<int, int> to, vector<pair<pair<int, int>, pair<int, int>>>& trace, bool& found);
	float Evaluation(bool player);
	float EuclideanDistance(float x1, float y1, float x2, float y2);
	int Winner();
	void MovePiece(pair<int, int>& from, pair<int, int>& to);

private:
	Input& input;

	int plyDepth;

	// vector to save goal locations;
	set<pair<int, int>> blackGoal;
	set<pair<int, int>> whiteGoal;
};

