#pragma once
#include <string>
using namespace std;
#include "Predicate.h"

class KnowledgeBase {
public:
	void Tell(string& fact);
	bool Ask(string& query);
};

