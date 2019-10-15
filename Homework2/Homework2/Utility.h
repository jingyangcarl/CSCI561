#pragma once

typedef struct InputParameter {
public:

public:
	bool gameOption;	// SINGLE(0) or GAME(1)
	bool player;		// BLACK(0) OR WHITE(1)
	float timeLeft;
	char** board;
} Input;