#include "UCSProcessor.h"

void UCSProcessor::UniformCostSearchNonrecursionEntrance() {
	for (auto i = input.destinations.begin(); i != input.destinations.end(); i++) {
		(*i).second.clear();
		UniformCostSearchNonrecursion((*i).first);
	}
}

void UCSProcessor::UniformCostSearchNonrecursion(const Location targetLoc) {
	
}
