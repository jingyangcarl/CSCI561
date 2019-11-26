#pragma once
#include "Predicate.h"

class DisjunctiveNormalForm {
public:
	DisjunctiveNormalForm(string& fact);

protected:
	bool isValidForm();
	void Str2DNF();

private:
	string fact_str;
	vector<Predicate> sentence;
};

typedef DisjunctiveNormalForm DNF;