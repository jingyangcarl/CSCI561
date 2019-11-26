#pragma once
#include "Predicate.h"
#include <set>
using namespace std;

class DisjunctiveNormalForm {
public:
	DisjunctiveNormalForm(string& fact);
	int Size();
	Predicate Begin() const;

	bool operator==(const DisjunctiveNormalForm& operand) const;

protected:
	bool isValidForm();
	void Str2DNF();

private:
	string fact_str;
	set<Predicate> predicates;
};

typedef DisjunctiveNormalForm DNF;