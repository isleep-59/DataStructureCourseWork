#pragma once
#include "Head.h"

class Employee {
private:
	string number, name, phone;

public :
	Employee() {
		number = "";
		name = "";
		phone = "";
	}

	Employee(string number, string name, string phone) {
		this->number = number;
		this->name = name;
		this->phone = phone;
	}

	string getNumber() {
		return number;
	}

	string getName() {
		return name;
	}

	string getPhone() {
		return phone;
	}

	void display() {
		cout << setw(20) << setfill(' ') << left << number;
		cout << setw(20) << setfill(' ') << left << name;
		cout << setw(20) << setfill(' ') << left << phone << endl;
	}
};