#pragma once
#include "Employee.h"

class EmployeeMap {
private:
	bool vis[MAX_SIZE];
	Employee mp[MAX_SIZE];
	string number_title, name_title, phone_title;

public:
	EmployeeMap() {
		freopen("employee.txt", "r", stdin);

		memset(vis, 0, sizeof(vis));
		string number, name, phone;	
		cin >> number_title >> name_title >> phone_title;
		while (cin >> number >> name >> phone) {
			Employee tmp(number, name, phone);
			add(tmp);
		}

		freopen("CON", "r", stdin);
		cin.clear();
	}

	bool check(int idx) {
		if (vis[idx])
			return true;
		else
			return false;
	}

	bool add(Employee tmp) {
		//mp.insert(make_pair(tmp.getNumber(), tmp));
		int idx = stoi(tmp.getNumber());
		if (!vis[idx])
			vis[idx] = true;
		else
			return false;
		mp[idx] = tmp;
		return true;
	}

	bool del(string number) {
		//mp.erase(mp.find(number));
		int idx = stoi(number);
		if (vis[idx])
			vis[idx] = false;
		else
			return false;
		return true;
	}

	bool modify(string number, Employee tmp) {
		if (!del(number))
			return false;
		add(tmp);
		return true;
	}

	Employee query(int idx) {
		return mp[idx];
	}

	void title() {
		cout << setw(20) << setfill(' ') << left << number_title;
		cout << setw(20) << setfill(' ') << left << name_title;
		cout << setw(20) << setfill(' ') << left << phone_title << endl;
	}

	void display() {
		title();
		for (int i = 0; i < MAX_SIZE; ++i) {
			if (vis[i])
				mp[i].display();
		}
	}
};