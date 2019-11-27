#pragma once
#include <string>
using namespace std;
#include "Predicate.h"
#include "DisjunctiveNormalForm.h"

class KnowledgeBase {
public:
	void Tell(string& fact);
	bool Ask(string& query);

protected:


private:
	set<Predicate> knowledge;
	vector<DisjunctiveNormalForm> inferenceRule;
};

