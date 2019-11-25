#include "Predicate.h"

/*
Description:
This function is a constructor;
Input:
@ string& predicateStr: a string denotes a predicate;
Output:
@ Preciate returnValue: a predicate;
*/
Predicate::Predicate(string& predicate_str) {
	this->predicate_str = predicate_str;
	if (SyntaxCheck()) {
		PreciateStringSplit();
		Print();
	}
}

/*
Description:
This function is used to negate the predicate;
Input:
@ void parameter: void;
Output:
@ void returnValie: void;
*/
void Predicate::negate() {
	this->negation = !this->negation;
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
This function is used to detect if the given predicate_str is a valid predicate string;
Input:
@ void parameter: void;
Output:
@ bool returnValie: if the given predicate_str is a valid predicate string;
*/
bool Predicate::SyntaxCheck() {
	// illegal characters
	if (this->predicate_str.find('&') != string::npos) return false;
	if (this->predicate_str.find('|') != string::npos) return false;
	if (this->predicate_str.find('=') != string::npos) return false;
	if (this->predicate_str.find('>') != string::npos) return false;
	// legal characters
	if (this->predicate_str.find('(') == string::npos) return false;
	if (this->predicate_str.find(')') == string::npos) return false;
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
void Predicate::PreciateStringSplit() {
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
	cout << predicate_str_copy << endl;
	while (int pos = predicate_str_copy.find(',') != string::npos) {

		string argument = predicate_str_copy.substr(0, pos);
		this->arguments.push_back(argument);
		predicate_str_copy.erase(0, pos);
	}
}
