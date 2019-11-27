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
#include <set>
using std::set;
#include <map>>
using std::map;
using std::pair;
#include <sstream>
using std::stringstream;

class Predicate {
public:
	Predicate(const string& predicate_str, bool negate = false);
	Predicate(const Predicate& predicate);

	void Print();
	bool isValid();
	string getActionStr() const;
	int getvariableNum() const;
	map<string, string> Unification(Predicate& predicate_query) const;
	void Replace(map<string, string>& variableConstantMap);

	// operator overwrite
	Predicate& operator-() const;
	bool operator<(const Predicate& predicate) const;
	bool operator==(const Predicate& operand) const;

protected:
	bool isSyntaxValid();
	void PreciateStringSegmentation();

private:
	string predicate_str;
	bool validity; // used to denote if the Predicate is valid or not

	bool negation;
	string action_str;
	vector<string> arguments;
	set<int> variableIndex;
};

