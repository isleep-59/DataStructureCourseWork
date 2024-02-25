#pragma once
#include "Head.h"
#include "Employee.h"

class Manager : public Employee {
private:
	string job;

public:
	Manager() : Employee() {
		job = "";
	}

	Manager(string number, string name, string phone, string job) : Employee(number, name, phone) {
		this->job = job;
	}

	string getJob() {
		return job;
	}

	void display() {
		cout << setw(20) << setfill(' ') << left << getNumber();
		cout << setw(20) << setfill(' ') << left << getName();
		cout << setw(20) << setfill(' ') << left << getPhone();
		cout << setw(20) << setfill(' ') << left << job << endl;
	}
};