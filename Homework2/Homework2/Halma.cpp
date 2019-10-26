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
				blackGoal.insert(pair<int, int>(BOARDSIZE - 1 - i, BOARDSIZE - 1 - j));
			}
		}
	}

	// white goals are initial black pieces' lcoaiton, which is the upper triangle
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (i + j < 6 && i != 5 && j != 5) {
				whiteGoal.insert(pair<int, int>(i, j));
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
	Minimax(this->plyDepth, input.player, input.timeLeft, true, -FP_INFINITE, FP_INFINITE);

	Output();

	// move piece
	MovePiece(bestMove.first, bestMove.second);

}

void Halma::Output() {
	cout << "from: (" << bestMove.first.first << ", " << bestMove.first.second << ")" << endl;
	cout << "to: (" << bestMove.second.first << ", " << bestMove.second.second << ")" << endl;
}

void Halma::Output2File() {
	ofstream output("input.txt");
	if (output.is_open()) {
		output << (input.gameOption ? "GAME" : "SINGLE") << endl;
		output << (!input.player ? "WHITE" : "BLACK") << endl;
		output << input.timeLeft << endl;
		for (int i = 0; i < BOARDSIZE; i++) {
			for (int j = 0; j < BOARDSIZE; j++) {
				output << input.board[i][j];
			}
			output << endl;
		}
	}
	output.close();
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
float Halma::Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing, float alpha, float beta) {

	float bestVal(0);

	if (plyDepth == 0 || Winner() != -1 || clock() / CLOCKS_PER_SEC >= timeLeft) {
		return Evaluation(player);
	}

	map<pair<int, int>, vector<pair<int, int>>> moves;
	if (maxing) {
		bestVal = -FP_INFINITE;
		moves = GetNextMoves(player);
	}
	else {
		bestVal = FP_INFINITE;
		moves = GetNextMoves(!player);
	}

	// loop through all possible moves
	for (auto i = moves.begin(); i != moves.end(); i++) {

		pair<int, int> from = (*i).first;

		for (auto j = (*i).second.begin(); j != (*i).second.end(); j++) {

			pair<int, int> to = (*j);

			if (clock() / CLOCKS_PER_SEC >= timeLeft) {
				return bestVal;
			}

			// move the piece to possible destination
			MovePiece(from, to);

			// recursion
			float value = Minimax(plyDepth - 1, player, timeLeft, !maxing, alpha, beta);

			// move the piece back
			MovePiece(to, from);

			// update alpha
			if (maxing && value > bestVal) {
				bestVal = value;
				bestMove.first = from;
				bestMove.second = to;
				alpha = fmaxf(alpha, value);
			}

			// update beta
			if (!maxing && value < bestVal) {
				bestVal = value;
				bestMove.first = from;
				bestMove.second = to;
				beta = fminf(beta, value);
			}

			// pruning
			if (beta <= alpha) {
				return bestVal;
			}

		}

	}

	return bestVal;
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

	auto moves = new map<pair<int, int>, vector<pair<int, int>>>();

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

			// if the piece is in self campus, no limitation
			// if the piece is in public area, the piece cannot move back
			// if the piece is in enemy campus, the piece cannot go back to the public

			set<pair<int, int>> toSet;
			set<pair<int, int>> toSetPublic;
			set<pair<int, int>> toSetSelf;
			set<pair<int, int>> toSetEnemy;
			if (player) {
				// current player is WHITE

				// classify possible moves
				for (auto iter = to.begin(); iter != to.end(); iter++) {
					
					if (blackGoal.find(*iter) != blackGoal.end()) {
						toSetSelf.insert(*iter);
					} 
					else if (whiteGoal.find(*iter) != whiteGoal.end()) {
						toSetEnemy.insert(*iter);
					}
					else {
						toSetPublic.insert(*iter);
					}
				}

				if (blackGoal.find(from) != blackGoal.end()) {
					// the current piece is in self campus
					toSet.insert(toSetPublic.begin(), toSetPublic.end());
					toSet.insert(toSetSelf.begin(), toSetSelf.end());
					toSet.insert(toSetEnemy.begin(), toSetEnemy.end());
				}
				else if (whiteGoal.find(from) != whiteGoal.end()) {
					// the current piece is in enemy campus
					toSet.insert(toSetEnemy.begin(), toSetEnemy.end());
				}
				else {
					// the current piece is in public area
					toSet.insert(toSetEnemy.begin(), toSetEnemy.end());
					toSet.insert(toSetPublic.begin(), toSetPublic.end());
				}

			}
			else {
				// current player is BLACK

				// classify possible moves
				for (auto iter = to.begin(); iter != to.end(); iter++) {

					if (whiteGoal.find(*iter) != whiteGoal.end()) {
						toSetSelf.insert(*iter);
					}
					else if (blackGoal.find(*iter) != blackGoal.end()) {
						toSetEnemy.insert(*iter);
					}
					else {
						toSetPublic.insert(*iter);
					}
				}

				if (whiteGoal.find(from) != whiteGoal.end()) {
					// the current piece is in self campus
					toSet.insert(toSetPublic.begin(), toSetPublic.end());
					toSet.insert(toSetSelf.begin(), toSetSelf.end());
					toSet.insert(toSetEnemy.begin(), toSetEnemy.end());
				}
				else if (blackGoal.find(from) != blackGoal.end()) {
					// the current piece is in enemy campus
					toSet.insert(toSetEnemy.begin(), toSetEnemy.end());
				}
				else {
					// the current piece is in public area
					toSet.insert(toSetEnemy.begin(), toSetEnemy.end());
					toSet.insert(toSetPublic.begin(), toSetPublic.end());
				}
			}

			to.clear();
			for (auto iter = toSet.begin(); iter != toSet.end(); iter++) {
				to.push_back(*iter);
			}
			
			moves->insert(pair<pair<int, int>, vector<pair<int, int>>>(from, to));
		}
	}

	return *moves;
}

/*
Description:
This function is used to get all possible jumps from "from" location and add it to "to" list;
Input:
@ pair<int, int> from: jump from point;
@ vector<pair<int, int>>& to: jump to point
Output:
@ void returnValue: void;
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

/*

*/
float Halma::Evaluation(bool player) {

	float value(0);

	// loop through all the pieces and find the largest distance from current piece to the goal
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {

			if (input.board[i][j] == 'B') {
				// if the current locaiton is a BLACK piece

				float maxDistance(-50);
				for (auto iter = blackGoal.begin(); iter != blackGoal.end(); iter++) {
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

				float maxDistance(-50);
				for (auto iter = whiteGoal.begin(); iter != whiteGoal.end(); iter++) {
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
	value = (player == true ? -value : value);

	return value;
}

/*
Description:
This function is used to calculate Euclidean distance given two location (x1, y1) and (x2, y2);
Input:
@ float x1: x1;
@ float y1: y1;
@ float x2: x2;
@ float y2: y2;
Output:
@ float returnValie: Euclidean distance;
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

	set<pair<int, int>>::iterator iter;

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
This function is used to move piece from (fromX, fromY) to (toX, toY);
Input:
@ pair<int, int> from: from location
@ pair<int, int> to: to location
Output:
@ auto returnValie: auto;
*/
void Halma::MovePiece(pair<int, int>& from, pair<int, int>& to) {
	char temp = input.board[to.first][to.second];
	input.board[to.first][to.second] = input.board[from.first][from.second];
	input.board[from.first][from.second] = temp;
}
