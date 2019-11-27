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

	void Print();
	bool isValid();

	// operator overwrite
	Predicate& operator-() const;
	bool operator<(const Predicate& predicate) const;
	bool operator==(const Predicate& operand) const;

protected:
	bool isSyntaxValid();
	void PreciateStringSegmentation();

private:
	string predicate_str;
	bool validity; // used to denote if the predicate is valid or not
	int variableNum;

	bool negation;
	string action_str;
	vector<string> arguments;
};

