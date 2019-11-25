#include "Input.h"

void InputParameter::Print() {
	cout << "---Input---" << endl;
	cout << "Number of Queries: " << this->querySize << endl;
	for (auto& query : queries) {
		cout << query << endl;
	}
	cout << "Number of Sentences: " << this->sentenceSize << endl;
	for (auto& sentence : sentences) {
		cout << sentence << endl;
	}
	cout << endl;
}
