#pragma once
#include <string>
#include <map>
#include <stack>
using namespace std;
#include "Predicate.h"
#include "DisjunctiveNormalForm.h"

class KnowledgeBase {
public:
	void Tell(string& fact);
	bool Ask(string& query);

protected:

private:
	set<Predicate> knowledges;
	vector<DisjunctiveNormalForm> inferenceRules;

};

