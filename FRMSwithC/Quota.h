#pragma once
#include "Head.h"

class Quota {
private:
	string number, job;
	int limits;

public:
	Quota() {
		number = "";
		job = "";
		limits = 0;
	}

	Quota(string number, string job, int limits) {
		this->number = number;
		this->job = job;
		this->limits = limits;
	}

	string getNumber() {
		return number;
	}

	string getJob() {
		return job;
	}

	int getLimits() {
		return limits;
	}

	void display() {
		cout << setw(20) << setfill(' ') << left << number;
		cout << setw(20) << setfill(' ') << left << job;
		cout << setw(20) << setfill(' ') << left << limits << endl;
	}
};