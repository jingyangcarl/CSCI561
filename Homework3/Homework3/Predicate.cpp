#include "Predicate.h"

/*
Description:
This function is a constructor;
Input:
@ const string& predicateStr: a string denotes a predicate;
Output:
@ Preciate returnValue: a predicate;
*/
Predicate::Predicate(const string& predicate_str) {
	this->predicate_str = predicate_str;
	if (SyntaxCheck()) {
		this->validity = true;
		PreciateStringSegmentation();
	}
	else {
		this->validity = false;
	}
}

/*
Description:
This function is a constructor;
Input:
@ const Predicate& predicate: a predicate object;
Output:
@ Predicate returnValie: a predicate;
*/
Predicate::Predicate(const Predicate& predicate) {
	this->predicate_str = predicate.predicate_str;
	this->negation = predicate.negation;
	this->action = predicate.action;
	this->arguments = predicate.arguments;
	this->validity = predicate.validity;
	this->variableNum = predicate.variableNum;
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
	cout << "Action: " << this->action << endl;
	cout << "Arguments: ";
	for (auto& argument : this->arguments) {
		cout << argument << ", ";
	}
	cout << endl;
}

/*
Description:
This function is used to return if the current predicate is a valid predicate;
Input:
@ void parameter: void;
Output:
@ bool returnValue: validity;
*/
bool Predicate::isValid() {
	return this->validity;
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

bool Predicate::operator<(const Predicate& predicate) const {
	if (this->arguments == predicate.arguments) {

	}
	else if (this->arguments < predicate.arguments) {
		this->action < predicate.action;
	}
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
	if (this->action != operand.action) return false;
	if (this->variableNum != operand.variableNum) return false;
	for (size_t i = 0; i < this->arguments.size(); i++) {
		if (arguments[i] != operand.arguments[i]) {
			return false;
		}
	}
	return true;
}

/*
Description:
This function is used to detect if the given predicate_str is a valid predicate string;
Input:
@ void parameter: void;
Output:
@ bool returnValie: if the given predicate_str is a valid predicate string;
*/
bool Predicate::SyntaxCheck() {
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
This function is used to split a valid predicate string and get negation mark, action string, and arguments
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
	this->action = predicate_str_copy.substr(0, pos);
	predicate_str_copy.erase(0, pos); // remove action string

	// get arguments
	predicate_str_copy.erase(0, 1); // remove left parentheses
	predicate_str_copy.erase(predicate_str_copy.size() - 1); // remove right parentheses
	while ((pos = predicate_str_copy.find(',')) != string::npos) {
		string argument = predicate_str_copy.substr(0, pos);
		this->arguments.push_back(argument);
		if (argument.size() == 1 && islower(argument[0])) variableNum++; 
		predicate_str_copy.erase(0, pos + 1); // remove argument and comma
	}
	this->arguments.push_back(predicate_str_copy); // add last argument
	if (predicate_str_copy.size() == 1 && islower(predicate_str_copy[0])) variableNum++;

}
