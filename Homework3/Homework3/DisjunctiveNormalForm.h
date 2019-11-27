#pragma once
#include "Predicate.h"
#include <set>
using namespace std;

class DisjunctiveNormalForm {
public:
	DisjunctiveNormalForm(string& fact);
	int size();
	set<Predicate>::iterator begin() const;

	bool operator==(const DisjunctiveNormalForm& operand) const;

protected:
	bool isSyntaxValid();
	void Str2DNF();

private:
	string dnf_str;
	set<Predicate> predicates;
};

typedef DisjunctiveNormalForm DNF;