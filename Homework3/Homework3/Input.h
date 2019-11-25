#pragma once
#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;
using std::cout;
using std::endl;

typedef struct InputParameter {
public:
	void Print();

public:
	int querySize;
	int sentenceSize;
	vector<string> queries;
	vector<string> sentences;
};