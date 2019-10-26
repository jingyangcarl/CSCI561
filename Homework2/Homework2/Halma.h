#pragma once
#include <ctime>
#include "Input.h"
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class Halma {
public:
	Halma(Input& input);
	void run();
	void Output();
	void Output2File();

protected:
	pair<float, pair<pair<int, int>, pair<int, int>>>& Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing, float alpha, float beta);
	map<pair<int, int>, vector<pair<int, int>>>& GetNextMoves(bool player);
	void GetNextMoves(pair<int, int> from, vector<pair<int, int>>& moves);
	float Evaluation(bool player);
	float EuclideanDistance(float x1, float y1, float x2, float y2);
	int Winner();
	void MovePiece(pair<int, int>& from, pair<int, int>& to);

private:
	Input& input;

	int plyDepth;

	// vector to save goal locations;
	vector<pair<int, int>> blackGoal;
	vector<pair<int, int>> whiteGoal;

	// best move
	pair<float, pair<pair<int, int>, pair<int, int>>> bestMove;

};

