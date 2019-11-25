#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::remove_if;
#include <iostream>
using std::cout;
using std::endl;

class Predicate {
public:
	Predicate(string& predicate_str);
	void negate();
	void Print();

protected:
	bool SyntaxCheck();
	void PreciateStringSplit();

private:
	string predicate_str;
	bool negation;
	string action;
	vector<string> arguments;
};

