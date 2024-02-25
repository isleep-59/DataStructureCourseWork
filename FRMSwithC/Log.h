#pragma once
#include "Head.h"

class Log {
private:
	SYSTEMTIME date;
	string employee, manager, status;
	int money;

public:
	Log() {
		GetLocalTime(&date);
		employee = manager = status = "";
		money = 0;
	}

	Log(string employee, int money) {
		this->employee = employee;
		this->money = money;
		GetLocalTime(&date);
		
		status = "´´½¨";
	}

	string getEmployeeNumber() {
		return employee;
	}

	string getStatus() {
		return status;
	}

	SYSTEMTIME getDate() {
		return date;
	}

	int getMoney() {
		return money;
	}

	void changeStatus(string status) {
		this->status = status;
	}

	void changeManager(string manager) {
		this->manager = manager;
	}

	void display() {
		cout << setw(20) << setfill(' ') << left << employee;
		cout << setw(20) << setfill(' ') << left << money;
		cout << date.wYear;
		cout << setw(2) << setfill('0') << right << date.wMonth;
		cout << setw(2) << setfill('0') << right << date.wDay;
		cout << setw(12) << setfill(' ') << ' ';
		cout << setw(20) << setfill(' ') << left << status;
		cout << setw(20) << setfill(' ') << left << manager << endl;
	}
};