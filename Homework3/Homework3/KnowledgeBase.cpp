#include "KnowledgeBase.h"

void KnowledgeBase::Tell(string& fact_str) {

	DNF fact(fact_str);
	if (fact.Size() == 1) {
		knowledge.insert(fact.Begin());
	}
	else {
		inferenceRule.push_back(fact);
	}

}

bool KnowledgeBase::Ask(string& query) {
	return false;
}
