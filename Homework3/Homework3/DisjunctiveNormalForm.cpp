#include "DisjunctiveNormalForm.h"

DisjunctiveNormalForm::DisjunctiveNormalForm(string& fact_str) {
	this->fact_str = fact_str;
	if (isValidForm()) {
		Str2DNF();
	}
}

int DisjunctiveNormalForm::Size() {
	return this->predicates.size();
}

Predicate DisjunctiveNormalForm::Begin() const {
	return *predicates.begin();
}

bool DisjunctiveNormalForm::operator==(const DisjunctiveNormalForm& operand) const {
	if (this->predicates.size() != operand.predicates.size()) return false;
	return this->predicates == operand.predicates;
}

bool DisjunctiveNormalForm::isValidForm() {
	if (this->fact_str.find('|') != string::npos) {
		cout << "Invalide '|' in \"" << this->fact_str << "\"" << endl;
		return false;
	}
}

void DisjunctiveNormalForm::Str2DNF() {
	int pos(0);
	if ((pos = this->fact_str.find("=>")) != string::npos) {
		// implication form

		// get antecedent string and consequent string
		string antecedent_str = fact_str.substr(0, pos);
		string consequent_str = fact_str.substr(pos + 2); // "=>" length is 2

		// move white spaces
		antecedent_str.erase(remove_if(antecedent_str.begin(), antecedent_str.end(), isspace), antecedent_str.end());
		consequent_str.erase(remove_if(consequent_str.begin(), consequent_str.end(), isspace), consequent_str.end());

		// split antecedent over & and save to the predicates
		string antecedent_str_copy = antecedent_str;
		while ((pos = antecedent_str_copy.find('&')) != string::npos) {
			string predicate_str = antecedent_str_copy.substr(0, pos);
			Predicate predicate_antecedent(predicate_str);
			if (predicate_antecedent.isValid()) {
				predicates.insert(-predicate_antecedent);
				antecedent_str_copy = antecedent_str_copy.substr(pos + 1); // "&" length is 1
			}
		}
		Predicate predicate_antecedent(antecedent_str_copy);
		if (predicate_antecedent.isValid()) {
			predicates.insert(-predicate_antecedent);
		}

		// save consequent to the predicates
		Predicate  predicate_consequent(consequent_str);
		if (predicate_antecedent.isValid()) {
			predicates.insert(predicate_consequent);
		}
	}
	else {
		// single literal
		Predicate predicate(fact_str);
		if (predicate.isValid()) {
			predicates.insert(predicate);
		}
	}
}
