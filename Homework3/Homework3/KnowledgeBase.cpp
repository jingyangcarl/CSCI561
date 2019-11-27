#include "KnowledgeBase.h"

void KnowledgeBase::Tell(string& fact_str) {

	DNF fact(fact_str);
	if (fact.size() == 1) {
		knowledge.insert(*fact.begin());
	}
	else {
		inferenceRule.push_back(fact);
	}
}

bool KnowledgeBase::Ask(string& query) {

	Predicate predicate(query);
	if (!predicate.isValid()) return false;

	if (knowledge.find(predicate) != knowledge.end()) return true;

	return false;
}
