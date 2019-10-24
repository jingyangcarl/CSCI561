#include "Halma.h"

/*
Description:
This function is a constructor;
Input:
@ Input& input: input parameter including Halma game option, player, left time, and board;
Output:
@ Halma returnvalue: a Halma object;
*/
Halma::Halma(Input& input) :
	input(input) {

	// define minimax depth
	this->plyDepth = 3;

	// init goals for black pieces and white pieces
	// black goals are initial white pieces' location, which the lower triangle
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (i + j < 6 && i != 5 && j != 5) {
				blackGoal.push_back(pair<int, int>(BOARDSIZE - 1 - i, BOARDSIZE - 1 - j));
			}
		}
	}

	// white goals are initial black pieces' lcoaiton, which is the upper triangle
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (i + j < 6 && i != 5 && j != 5) {
				whiteGoal.push_back(pair<int, int>(i, j));
			}
		}
	}
}

/*
Description:
This function is a trigger of recursion Minimax;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void Halma::run() {
	Minimax(this->plyDepth, input.player, input.timeLeft);
}

/*
Description:

Input:
@ int plyDepth: depth of the minimax tree;
@ bool player: current player;
@ timer_t timerLeft: left timer in seconds;
@ bool maxing: if the current layer is to do maximization;
Output:

*/
float Halma::Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing) {

	if (plyDepth == 0) {
		Evaluation();
	}
	return 0.0f;
}

/*

*/
float Halma::Evaluation() {

	float value(0);

	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {

			if (input.board[i][j] == 'B') {
				// if the current locaiton is a BLACK piece

				float maxDistance(0);
				for (vector<pair<int, int>>::iterator iter = blackGoal.begin(); iter != blackGoal.end(); iter++) {
					float distance = EuclideanDistance(i, j, (*iter).first, (*iter).second);
					maxDistance = distance > maxDistance ? distance : maxDistance;
				}

			}
			else if (input.board[i][j] == 'W') {
				// if the current locaiton is a WHITE piece

				float maxDistance(0);
				for (vector<pair<int, int>>::iterator iter = whiteGoal.begin(); iter != whiteGoal.end(); iter++) {
					float distance = EuclideanDistance(i, j, (*iter).first, (*iter).second);
					maxDistance = distance > maxDistance ? distance : maxDistance;
				}

			}
		}
	}

	return value;
}

float Halma::EuclideanDistance(float x1, float y1, float x2, float y2) {
	return sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
}
