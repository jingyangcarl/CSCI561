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

	Predicate predicate(query, true);
	vector<DisjunctiveNormalForm> toUnify = this->inferenceRule;
	while (!toUnify.empty()) {
		DNF rule_current = toUnify.front();
		toUnify.erase(toUnify.begin());
		if (!rule_current.has(predicate)) {
			continue;
		}
		DNF rule_new = rule_current.Unification(query);
	}
	return true;

}