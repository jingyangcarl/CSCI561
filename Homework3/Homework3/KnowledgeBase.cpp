#include "KnowledgeBase.h"

void KnowledgeBase::Tell(string& fact_str) {

	DNF fact(fact_str);
	if (fact.size() == 1) {
		knowledges.insert(*fact.begin());
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
		DNF rule_unified = rule_current.Unification(query);
		for (auto& knowledge : knowledges) {

			// check conflication
			if (-knowledge == predicate) {
				return true;
			}

			DNF rule_resolved = rule_unified.Resolution(knowledge);
			if (rule_resolved.size() == 1 && (*rule_resolved.begin()).getvariableNum() == 0) {
				knowledges.insert(*rule_resolved.begin());
			}
			else {
				toUnify.push_back(rule_resolved);
			}
		}

	}
	return false;

}