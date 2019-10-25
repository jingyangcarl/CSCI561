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

	if (plyDepth == 0 || Winner() != -1) {
		Evaluation(player);
	}

	float bestVal(0);

	if (maxing) {
		bestVal = LLONG_MAX;
		GetNextMoves(player);
	}
	else {
		bestVal = -LLONG_MAX;
		GetNextMoves(!player);
	}


	return 0.0f;
}

/*

*/
float Halma::Evaluation(bool player) {

	float value(0);

	// loop through all the pieces and find the largest distance from current piece to the goal
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {

			if (input.board[i][j] == 'B') {
				// if the current locaiton is a BLACK piece

				float maxDistance(0);
				for (vector<pair<int, int>>::iterator iter = blackGoal.begin(); iter != blackGoal.end(); iter++) {
					// if the piece at goal's location is White or Empty, calculate the distance
					if (input.board[(*iter).first][(*iter).second] != 'B'){
						float distance = EuclideanDistance(i, j, (*iter).first, (*iter).second);
						maxDistance = distance > maxDistance ? distance : maxDistance;
					}
				}
				value -= maxDistance;

			}
			else if (input.board[i][j] == 'W') {
				// if the current locaiton is a WHITE piece

				float maxDistance(0);
				for (vector<pair<int, int>>::iterator iter = whiteGoal.begin(); iter != whiteGoal.end(); iter++) {
					// if the piece at goal's location is Black or Empty, calculate the distance
					if (input.board[(*iter).first][(*iter).second] != 'W') {
						float distance = EuclideanDistance(i, j, (*iter).first, (*iter).second);
						maxDistance = distance > maxDistance ? distance : maxDistance;
					}
				}
				value += maxDistance;
			}
		}
	}

	// if player is White
	value = player == true ? -value : value;

	return value;
}

/*

*/
float Halma::EuclideanDistance(float x1, float y1, float x2, float y2) {
	return sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2));
}

/*
Description:
This function is used to decide if there is a winner in the current situation, where the winner has to take place all enemy's place
Input:
@ void parameter: void;
Output:
@ int returnValue: if there doesn't exist a winner, return -1, otherwise, black-win returns 0, white-win returns 1;
*/
int Halma::Winner() {

	vector<pair<int, int>>::iterator iter;

	for (iter = blackGoal.begin(); iter != blackGoal.end(); iter++) {
		// if black is the winner, all blackGoal should be black
		if (input.board[(*iter).first][(*iter).second] != 'B') break;
	}
	// winner is black
	if (iter == blackGoal.end()) return 0;

	for (iter = whiteGoal.begin(); iter != whiteGoal.end(); iter++) {
		if (input.board[(*iter).first][(*iter).second] != 'W') break;
	}
	// winner is white
	if (iter == whiteGoal.end()) return 1;

	// no winner
	return -1;
}

/*
Description:
This function is used to generate all legal moves for all pieces;
Input:
@ bool player: the current player;
Outout:
@ map<pair<int, int>, vector<pair<int, int>>> returnValue: a
*/
map<pair<int, int>, vector<pair<int, int>>>& Halma::GetNextMoves(bool player) {

	map<pair<int, int>, vector<pair<int, int>>>* moves = new map<pair<int, int>, vector<pair<int, int>>>();

	// loop through all the position on the board
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {
			// skip pieces that are not current player
			if (input.board[i][j] != (player ? 'W' : 'B')) continue;

			// generate legal moves from the current position
			pair<int, int> from = pair<int, int>(i, j);
			vector<pair<int, int>> to;

			// loop through all one step move
			for (int ii = -1; ii < 2; ii++) {
				for (int jj = -1; jj < 2; jj++) {

					// skip degenerate value
					if (ii == 0 && jj == 0) continue;

					// update current location
					int row = i + ii;
					int col = j + jj;

					// skip values not exist
					if (row < 0 || row >= BOARDSIZE || col < 0 || col >= BOARDSIZE) continue;

					if (input.board[row][col] == '.') {
						to.push_back(pair<int, int>(row, col));
					}

				}
			}

			// temperaly push the current location into "to" list, which is a place holder when appending possible jumps
			to.insert(to.begin(), from);
			// check all available jumps
			GetNextMoves(from, to);
			// remove the place holder
			to.erase(to.begin());

			// if there is legal move, add it
			if (to.empty()) continue;
			moves->insert(pair<pair<int, int>, vector<pair<int, int>>>(from, to));
		}
	}

	return *moves;
}

/*

*/
void Halma::GetNextMoves(pair<int, int> from, vector<pair<int, int>>& to) {

	// loop through 8 neighbors and check if jump is possible
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			// skip degenerate value
			if (i == 0 && j == 0) continue;

			int row = from.first + i;
			int col = from.second + j;

			// skip values not exist
			if (row < 0 || row >= BOARDSIZE || col < 0 || col >= BOARDSIZE) continue;
			// skip empty place
			if (input.board[row][col] == '.') continue;

			// jump through [row, col] is possible
			int jRow = from.first + 2 * i;
			int jCol = from.second + 2 * j;

			// skip values not exist
			if (jRow < 0 || jRow >= BOARDSIZE || jCol < 0 || jCol >= BOARDSIZE) continue;
			// jump is not possible if there is already any piece in the [jRow][jCol]
			if (input.board[jRow][jCol] != '.') continue;

			// [jRow][jCol] is a legal jump, add it to jump list if it's not exist
			pair<int, int> jump = pair<int, int>(jRow, jCol);
			vector<pair<int, int>>::iterator iter;
			for (iter = to.begin(); iter != to.end(); iter++) {
				if ((*iter) == jump) break;
			}
			if (iter == to.end()) {
				to.insert(to.begin() + 1, jump);
				GetNextMoves(jump, to);
			}

		}
	}
}
