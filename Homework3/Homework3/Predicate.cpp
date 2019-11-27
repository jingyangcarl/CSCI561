#include "Predicate.h"

/*
Description:
This function is a constructor;
Input:
@ const string& predicateStr: a string denotes a predicate_query;
Output:
@ Preciate returnValue: a predicate_query;
*/
Predicate::Predicate(const string& predicate_str, bool negate) {
	// remove white space
	this->predicate_str = predicate_str;
	this->predicate_str.erase(remove_if(this->predicate_str.begin(), this->predicate_str.end(), isspace), this->predicate_str.end());
	if (isSyntaxValid()) {
		this->validity = true;
		PreciateStringSegmentation();
		this->negation = (negate ? !this->negation : this->negation);
	}
	else {
		this->validity = false;
	}
}

/*
Description:
This function is a constructor;
Input:
@ const Predicate& predicate_query: a predicate_query object;
Output:
@ Predicate returnValie: a predicate_query;
*/
Predicate::Predicate(const Predicate& predicate) {
	this->predicate_str = predicate.predicate_str;
	this->negation = predicate.negation;
	this->action_str = predicate.action_str;
	this->arguments = predicate.arguments;
	this->validity = predicate.validity;
}

/*
Description:
This function is used to print a Predicate;
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void Predicate::Print() {
	cout << "---Predicate---" << endl;
	cout << "Predicate String: " << this->predicate_str << endl;
	cout << "Negation: " << this->negation << endl;
	cout << "Action: " << this->action_str << endl;
	cout << "Arguments: ";
	for (auto& argument : this->arguments) {
		cout << argument << ", ";
	}
	cout << endl;
}

/*
Description:
This function is used to return if the current predicate_query is a valid predicate_query;
Input:
@ void parameter: void;
Output:
@ bool returnValue: validity;
*/
bool Predicate::isValid() {
	return this->validity;
}

string Predicate::getActionStr() const {
	return this->action_str;
	pair<string, string> Unfication(string& query);
}

int Predicate::getvariableNum() const {
	return this->variableIndex.size();
}

map<string, string> Predicate::Unification(Predicate& predicate_query) const {

	auto isVariable = [](const string& argument) {
		if (argument.size() > 1) return false;
		if (isupper(argument[0])) return false;
		return true;
	};

	map<string, string> variableConstantMap;
	for (int i = 0; i < arguments.size(); i++) {

		if (isVariable(arguments[i])) {
			// variable - constant
			if (variableConstantMap.find(arguments[i]) != variableConstantMap.end()) {
				variableConstantMap.clear();
			}
			variableConstantMap.insert(pair<string, string>(arguments[i], predicate_query.arguments[i]));
		}
		else {
			// constant - constant
			if (arguments[i] != predicate_query.arguments[i]) {
				variableConstantMap.clear();
			}
		}
	}
	return variableConstantMap;
}

void Predicate::Replace(map<string, string>& variableConstantMap) {

	for (int i = 0; i < arguments.size(); i++) {
		if (variableConstantMap.find(arguments[i]) != variableConstantMap.end()) {
			arguments[i] = variableConstantMap[arguments[i]];
		}
	}
	stringstream ss;
	ss << (this->negation ? "~" : "") << this->action_str << "(";
	for (int i = 0; i < this->arguments.size() - 1; i++) {
		ss << arguments[i] << ",";
	}
	ss << arguments[arguments.size() - 1] << ")";
	this->predicate_str = ss.str();
}

/*
Description:
This function is a overload of unary operator-;
Input:
@ void parameter: void;
Output:
@ Predicate& returnValue: a Predicate reference;
*/
Predicate& Predicate::operator-() const {
	Predicate* result = new Predicate(*this);
	result->negation = !result->negation;
	return *result;
}

/*
Description:
This function is a overwrite of operator< used to compare two predicate_query used for set sorting;
Input:
@ const Predicate& predicate_query: righthand predicate_query;
Output:
@ bool returnValue: if the righthand predicate_query is less than the left;
*/
bool Predicate::operator<(const Predicate& predicate) const {
	return this->predicate_str < predicate.predicate_str;
}

/*
Description:
This function is a overload of operator==
Input:
@ const Predicate& operand: a given operand;
Output:
@ bool returnValue: if the two predicates are the same;
*/
bool Predicate::operator==(const Predicate& operand) const {
	if (this->negation != operand.negation) return false;
	if (this->action_str != operand.action_str) return false;
	if (this->variableIndex.size() != operand.variableIndex.size()) return false;
	for (size_t i = 0; i < this->arguments.size(); i++) {
		if (arguments[i] != operand.arguments[i]) {
			return false;
		}
	}
	return true;
}

/*
Description:
This function is used to detect if the given predicate_str is a valid predicate_query string;
Input:
@ void parameter: void;
Output:
@ bool returnValie: if the given predicate_str is a valid predicate_query string;
*/
bool Predicate::isSyntaxValid() {
	// illegal characters
	if (this->predicate_str.find('&') != string::npos) {
		cout << "Invalide '&' in \"" << this->predicate_str << "\"" << endl;
		return false;
	}
	if (this->predicate_str.find('|') != string::npos) {
		cout << "Invalide '|' in \"" << this->predicate_str << "\"" << endl;
		return false;
	}
	if (this->predicate_str.find('=') != string::npos) {
		cout << "Invalide '=>' in \"" << this->predicate_str << "\"" << endl;
		return false;
	}
	if (this->predicate_str.find('>') != string::npos) {
		cout << "Invalide '>' in \"" << this->predicate_str << "\"" << endl;
		return false;
	}
	// legal characters
	if (this->predicate_str.find('(') == string::npos) {
		cout << "Missing '(' in \"" << this->predicate_str << "\"" << endl;
		return false;
	}
	if (this->predicate_str.find(')') == string::npos) {
		cout << "Missing ')' in \"" << this->predicate_str << "\"" << endl;
		return false;
	}
	return true;
}

/*
Description:
This function is used to split a valid predicate_query string and get negation mark, action_str string, and arguments
Input:
@ void parameter: void;
Output:
@ void returnValue: void;
*/
void Predicate::PreciateStringSegmentation() {
	// remove white space
	predicate_str.erase(remove_if(predicate_str.begin(), predicate_str.end(), isspace), predicate_str.end());
	string predicate_str_copy = this->predicate_str;

	// get negation
	this->negation = predicate_str_copy.find('~') != string::npos ? true : false;
	predicate_str_copy = this->negation ? predicate_str_copy.substr(1) : predicate_str_copy; // remove negation mark

	// get name
	int pos = predicate_str_copy.find('(');
	this->action_str = predicate_str_copy.substr(0, pos);
	predicate_str_copy.erase(0, pos); // remove action_str string

	// get arguments
	predicate_str_copy.erase(0, 1); // remove left parentheses
	predicate_str_copy.erase(predicate_str_copy.size() - 1); // remove right parentheses
	while ((pos = predicate_str_copy.find(',')) != string::npos) {
		string argument = predicate_str_copy.substr(0, pos);
		this->arguments.push_back(argument);
		if (argument.size() == 1 && islower(argument[0])) {
			variableIndex.insert(this->arguments.size() - 1);
		}
		predicate_str_copy.erase(0, pos + 1); // remove argument and comma
	}
	this->arguments.push_back(predicate_str_copy); // add last argument
	if (predicate_str_copy.size() == 1 && islower(predicate_str_copy[0])) {
		variableIndex.insert(this->arguments.size() - 1);
	}

}
