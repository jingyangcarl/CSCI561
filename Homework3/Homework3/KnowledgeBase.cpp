#include "KnowledgeBase.h"

void KnowledgeBase::Tell(string& fact) {
	string predicate_str = "~Alert(Bob, ASAIDs)";
	Predicate predicate(predicate_str);
}

bool KnowledgeBase::Ask(string& query) {
	return false;
}
