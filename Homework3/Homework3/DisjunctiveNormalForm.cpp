#include "DisjunctiveNormalForm.h"

DisjunctiveNormalForm::DisjunctiveNormalForm(string& fact_str) {
	this->dnf_str = fact_str;
	this->dnf_str.erase(remove_if(this->dnf_str.begin(), this->dnf_str.end(), isspace), this->dnf_str.end());
	if (isSyntaxValid()) {
		Str2DNF();
	}
}

/*
Description:
This function is used to get the number of predicates in the sentence;
Input:
@ void parameter: void;
Output:
@ int returnValue: the number of predicates in the dnf;
*/
int DisjunctiveNormalForm::size() const {
	return this->predicates.size();
}

/*
Description:
This function is used to get the first Predicate in the sentence;
Input:
@ void parameter: void;
Output:
@ set<Predicate>::const_iterator returnValue: a iterator point to the first Predicate in the sentence;
*/
set<Predicate>::const_iterator DisjunctiveNormalForm::begin() const {
	return predicates.begin();
}

bool DisjunctiveNormalForm::has(Predicate& predicate) const {
	return dnf_str.find(predicate.getActionStr()) != string::npos;
}

string DisjunctiveNormalForm::str() const {
	return dnf_str;
}

DisjunctiveNormalForm& DisjunctiveNormalForm::Unification(string& query) {

	DisjunctiveNormalForm* unifiedDNF = new DisjunctiveNormalForm(*this);

	Predicate predicate_query(query);
	map<string, string> variableConstantMap;
	for (auto& predicate : predicates) {
		if (predicate.getActionStr() == predicate_query.getActionStr()) {
			map<string, string> variableConstantMap_temp = predicate.Unification(predicate_query);
			for (auto& pair : variableConstantMap_temp) {
				variableConstantMap.insert(pair);
			}
		}
	}

	unifiedDNF->predicates.clear();
	for (auto& predicate : predicates) {
		Predicate predicate_unified(predicate);
		predicate_unified.Replace(variableConstantMap);
		unifiedDNF->predicates.insert(predicate_unified);
	}

	unifiedDNF->dnf_str = "";
	return *unifiedDNF;
}

bool DisjunctiveNormalForm::operator<(const DisjunctiveNormalForm& operand) const {
	return this->dnf_str < operand.dnf_str;
}

/*
Description:
This function is a overwrite of oeprator==;
Input:
@ const DisjunctiveNormalForm& operand: a reference to righthand side operand;
Output:
@ bool returnValue: if the two DisjuncitveNormalForm are the same;
*/
bool DisjunctiveNormalForm::operator==(const DisjunctiveNormalForm& operand) const {
	if (this->predicates.size() != operand.predicates.size()) return false;
	return this->predicates == operand.predicates;
}

/*
Description:
This function is used to detect if the input string is a valid disjunctive normal form;
Input:
@ void parameter: void;
Output:
@ bool returnValue: if the input string is a valid dnf;
*/
bool DisjunctiveNormalForm::isSyntaxValid() {
	if (this->dnf_str.find('|') != string::npos) {
		cout << "Invalide '|' in \"" << this->dnf_str << "\"" << endl;
		return false;
	}
}

/*
Description:
This function is used to convert dnf_str to disjunctive normal form;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void DisjunctiveNormalForm::Str2DNF() {
	int pos(0);
	if ((pos = this->dnf_str.find("=>")) != string::npos) {
		// implication form

		// get antecedent string and consequent string
		string antecedent_str = dnf_str.substr(0, pos);
		string consequent_str = dnf_str.substr(pos + 2); // "=>" length is 2

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
		Predicate predicate(dnf_str);
		if (predicate.isValid()) {
			predicates.insert(predicate);
		}
	}
}