#pragma once
#include "Predicate.h"
#include <set>
#include <map>
using namespace std;

class DisjunctiveNormalForm {
public:
	DisjunctiveNormalForm(string& fact);
	DisjunctiveNormalForm(Predicate& predicate);
	int size() const;
	set<Predicate>::iterator begin() const;
	bool has(Predicate& predicate) const;
	string str() const;
	DisjunctiveNormalForm& Unification(string& query);
	DisjunctiveNormalForm& Unification(const Predicate& predicate);
	DisjunctiveNormalForm& Resolution(const Predicate& predicate);

	bool operator<(const DisjunctiveNormalForm& operand) const;
	bool operator==(const DisjunctiveNormalForm& operand) const;

protected:
	bool isSyntaxValid();
	void Str2DNF();

private:
	string dnf_str;
	set<Predicate> predicates;
};

typedef DisjunctiveNormalForm DNF;