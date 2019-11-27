#include "KnowledgeBase.h"

void KnowledgeBase::Tell(string& fact_str) {

	DNF fact(fact_str);
	if (fact.size() == 1) {
		knowledges.insert(*fact.begin());
	}
	else {
		inferenceRules.push_back(fact);
	}
}

bool KnowledgeBase::Ask(string& query) {

	Predicate predicate(query, true);
	vector<DisjunctiveNormalForm> toDo = this->inferenceRules;
	while (!toDo.empty()) {
		DNF rule_current = toDo.front();
		toDo.erase(toDo.begin());
		if (!rule_current.has(predicate)) {
			continue;
		}
		DNF rule_unified = rule_current.Unification(query);
		for (auto& knowledge : knowledges) {
			DNF rule_resolved = rule_unified.Resolution(knowledge);
			if (rule_resolved.size() == 1 && (*rule_resolved.begin()).getVariableNum() == 0) {
				knowledges.insert(*rule_resolved.begin());
			}
			else {
				toDo.push_back(rule_resolved);
			}
		}

		for (auto& knowedge : knowledges) {

			// check conflication
			if (-knowedge == predicate) {
				return true;
			}

		}

	}
	return false;

	//Predicate predicate(query, true);
	//vector<DisjunctiveNormalForm> toDo;
	//toDo.push_back(DisjunctiveNormalForm(predicate));
	//while (!toDo.empty()) {
	//	DNF dnf_current = toDo.front();
	//	toDo.erase(toDo.begin());
	//	for (auto& inferenceRule : inferenceRules) {
	//		if (dnf_current.size() == 1) {
	//			DNF dnf_unified = inferenceRule.Unification(*dnf_current.begin());
	//			for (auto& knowledge : knowledges) {
	//				DNF dnf_resolved = dnf_unified.Resolution(knowledge);
	//				if (dnf_resolved.size() == 1 && (*dnf_resolved.begin()).getVariableNum() == 0) {
	//					knowledges.insert(*dnf_resolved.begin());
	//				}
	//				else {
	//					toDo.push_back(dnf_resolved);
	//				}
	//			}
	//		}

	//	}

	//	for (auto& knowedge : knowledges) {
	//		// check conflication
	//		if (-knowedge == predicate) {
	//			return true;
	//		}
	//	}
	//}
	//return false;

}