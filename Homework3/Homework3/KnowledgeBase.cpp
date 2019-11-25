#include "KnowledgeBase.h"

void KnowledgeBase::Tell(string& fact) {
	string predicate_str;
	predicate_str = "~Alert(Bob, ASAIDs)";
	Predicate predicate(predicate_str);
	cout << (predicate == -(-predicate)) << endl;
}

bool KnowledgeBase::Ask(string& query) {
	return false;
}
