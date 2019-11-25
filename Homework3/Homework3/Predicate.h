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
	Predicate(const string& predicate_str);
	Predicate(const Predicate& predicate);
	void negate();
	void Print();
	Predicate& operator-() const;
	bool operator==(const Predicate& operand) const;

protected:
	bool SyntaxCheck();
	void PreciateStringSegmentation();

private:
	string predicate_str;
	bool negation;
	string action;
	vector<string> arguments;
};

