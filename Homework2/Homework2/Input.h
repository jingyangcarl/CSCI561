#pragma once
#include <ctime>

#define BOARDSIZE 16

typedef struct InputParameter {
public:

public:
	bool gameOption;	// SINGLE(0) or GAME(1)
	bool player;		// BLACK(0) OR WHITE(1)
	time_t timeLeft;
	char** board;
} Input;