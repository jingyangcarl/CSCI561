#include "Halma.h"

#define LONG_MAX      2147483647L   // maximum (signed) long value

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
	this->plyDepth = 2;

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
	MinimaxReturn minimaxReturn = Minimax(this->plyDepth, input.player, input.timeLeft, true, -FP_INFINITE, FP_INFINITE);

	cout << "from: (" << minimaxReturn.from.first << ", " << minimaxReturn.from.second << ")" << endl;
	cout << "to: (" << minimaxReturn.to.first << ", " << minimaxReturn.to.second << ")" << endl;

	vector<pair<pair<int, int>, pair<int, int>>> trace;
	bool found(false);
	GetTrace(minimaxReturn.from, minimaxReturn.to, trace, found);

	// move piece
	MovePiece(minimaxReturn.from, minimaxReturn.to);

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
MinimaxReturn Halma::Minimax(int plyDepth, bool player, time_t timeLeft, bool maxing, float alpha, float beta) {

	MinimaxReturn bestReturn;
	
	if (plyDepth == 0 || Winner() != -1 || clock() / CLOCKS_PER_SEC >= timeLeft - 3) {
		bestReturn.value = Evaluation(player);
		return bestReturn;
	}

	map<pair<int, int>, vector<pair<int, int>>> moves;
	if (maxing) {
		bestReturn.value = -LONG_MAX;
		moves = GetNextMoves(player);
	}
	else {
		bestReturn.value = LONG_MAX;
		moves = GetNextMoves(!player);
	}

	for (auto i = moves.begin(); i != moves.end(); i++) {
		pair<int, int> from = (*i).first;

		set<pair<int, int>> toSet;
		for (auto iter = (*i).second.begin(); iter != (*i).second.end(); iter++) {
			toSet.insert(*iter);
		}
		if (player) {
			// white
			if (from.first == BOARDSIZE - 1 || from.second == BOARDSIZE - 1) {
				for (auto j = (*i).second.begin(); j != (*i).second.end(); j++) {
					auto to = (*j);
					if (to.first > from.first || to.second > from.second) {
						toSet.erase(to);
					}
				}
			}
		}
		else {
			// black
			if (from.first == 0 || from.second == 0) {
				for (auto j = (*i).second.begin(); j != (*i).second.end(); j++) {
					auto to = (*j);
					if (to.first < from.first || to.second < from.second) {
						toSet.erase(to);
					}
				}
			}
		}
		(*i).second.clear();
		for (auto iter = toSet.begin(); iter != toSet.end(); iter++) {
			(*i).second.push_back(*iter);
		}

		for (auto j = (*i).second.begin(); j != (*i).second.end(); j++) {
			pair<int, int> to = (*j);

			// if the piece is at the conner, move it
			if (!player && from.first == 0 && from.second == 0) {
				bestReturn.value = 10 * Evaluation(player);
				bestReturn.from = from;
				bestReturn.to = to;
				return bestReturn;
			}

			if (player && from.first == BOARDSIZE - 1 && from.second == BOARDSIZE - 1) {
				bestReturn.value = 10 * Evaluation(player);
				bestReturn.from = from;
				bestReturn.to = to;
				return bestReturn;
			}

			// if the piece is from camp and go outside, do it right away
			if (player) {
				// white

				if (blackGoal.find(from) != blackGoal.end() && blackGoal.find(to) == blackGoal.end()) {
					bestReturn.value = 10 * Evaluation(player);
					bestReturn.from = from;
					bestReturn.to = to;
					return bestReturn;
				}
			}
			else {
				// black
				if (whiteGoal.find(from) != whiteGoal.end() && whiteGoal.find(to) == whiteGoal.end()) {
					bestReturn.value = 10 * Evaluation(player);
					bestReturn.from = from;
					bestReturn.to = to;
					return bestReturn;
				}
			}
		}
	}

	// loop through all possible moves
	for (auto i = moves.begin(); i != moves.end(); i++) {

		pair<int, int> from = (*i).first;

		for (auto j = (*i).second.begin(); j != (*i).second.end(); j++) {

			pair<int, int> to = (*j);

			if (clock() / CLOCKS_PER_SEC >= timeLeft-3) {
				return bestReturn;
			}

			// move the piece to possible destination
			MovePiece(from, to);

			// recursion
			MinimaxReturn current = Minimax(plyDepth - 1, player, timeLeft, !maxing, alpha, beta);

			// move the piece back
			MovePiece(to, from);

			// update alpha
			if (maxing && current.value > bestReturn.value) {
				bestReturn.value = current.value;
				bestReturn.from = from;
				bestReturn.to = to;
				alpha = fmaxf(alpha, current.value);
			}

			// update beta
			if (!maxing && current.value < bestReturn.value) {
				bestReturn.value = current.value;
				bestReturn.from = from;
				bestReturn.to = to;
				beta = fminf(beta, current.value);
			}

			// pruning
			if (beta <= alpha) {
				return bestReturn;
			}

		}

	}

	return bestReturn;
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

void Halma::GetTrace(pair<int, int> from, pair<int, int> to, vector<pair<pair<int, int>, pair<int, int>>>& trace, bool& found) {


	if (abs(from.first - to.first) == 1 || abs(from.second - to.second) == 1) {
		ofstream output("output.txt");
		if (!output.is_open()) return;
		cout << "E " << from.first << ',' << from.second << ' ' << to.first << ',' << to.second << endl;
		output << "E " << from.second << ',' << from.first << ' ' << to.second << ',' << to.first << endl;
		output.close();
	}
	else {
		if (found) {
			return;
		}

		if (from == to) {
			found = true;
			ofstream output("output.txt");
			if (!output.is_open()) return;
			for (auto iter = trace.begin(); iter != trace.end(); iter++) {
				pair<int, int> from = (*iter).first;
				pair<int, int> to = (*iter).second;
				cout << "J " << from.first << ',' << from.second << ' ' << to.first << ',' << to.second << endl;
				output << "J " << from.second << ',' << from.first << ' ' << to.second << ',' << to.first << endl;
			}
			output.close();
			return;
		}

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

				auto jump = pair<int, int>(jRow, jCol);

				auto iter = trace.begin();
				for (iter = trace.begin(); iter != trace.end(); iter++) {
					if ((*iter).first == jump) break;
					if ((*iter).second == jump) break;
				}
				if (iter == trace.end()) {
					trace.push_back(pair<pair<int, int>, pair<int, int>>(from, jump));
					GetTrace(jump, to, trace, found);
					trace.pop_back();
				}
			}
		}
	}
}

/*

*/
float Halma::Evaluation(bool player) {

	float value(0);

	// loop through all the pieces and find the largest distance from current pieces to the goals
	for (int i = 0; i < BOARDSIZE; i++) {
		for (int j = 0; j < BOARDSIZE; j++) {

			if (input.board[i][j] == 'B') {
				// if the current locaiton is a BLACK piece

				float maxDistance(0);

				for (auto iter = blackGoal.begin(); iter != blackGoal.end(); iter++) {
					// if the piece at goal's location is White or Empty, calculate the distance
					if (input.board[(*iter).first][(*iter).second] != 'B'){
						float distance = EuclideanDistance(i, j, (*iter).first, (*iter).second);
						maxDistance = distance > maxDistance ? distance : maxDistance;
					}
				}

				if (whiteGoal.find(pair<int, int>(i, j)) != whiteGoal.end()) {
					maxDistance /= 2;
				}

				value -= maxDistance;

			}
			else if (input.board[i][j] == 'W') {
				// if the current locaiton is a WHITE piece

				float maxDistance(0);
				for (auto iter = whiteGoal.begin(); iter != whiteGoal.end(); iter++) {
					// if the piece at goal's location is Black or Empty, calculate the distance
					if (input.board[(*iter).first][(*iter).second] != 'W') {
						float distance = EuclideanDistance(i, j, (*iter).first, (*iter).second);
						maxDistance = distance > maxDistance ? distance : maxDistance;
					}
				}

				if (blackGoal.find(pair<int, int>(i, j)) != blackGoal.end()) {
					maxDistance /= 2;
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
