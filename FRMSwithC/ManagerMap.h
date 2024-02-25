#pragma once
#include "Manager.h"

class ManagerMap {
private:
	bool vis[MAX_SIZE];
	Manager mp[MAX_SIZE];
	string number_title, name_title, phone_title, job_title;

public:
	ManagerMap() {
		freopen("manager.txt", "r", stdin);

		memset(vis, 0, sizeof(vis));
		string number, name, phone, job;
		cin >> number_title >> name_title >> phone_title >> job_title;
		while (cin >> number >> name >> phone >> job) {
			Manager tmp(number, name, phone, job);
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

	bool add(Manager tmp) {
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

	bool modify(string number, Manager tmp) {
		if (!del(number))
			return false;
		add(tmp);
		return true;
	}

	Manager query(int idx) {
		return mp[idx];
	}

	void title() {
		cout << setw(20) << setfill(' ') << left << number_title;
		cout << setw(20) << setfill(' ') << left << name_title;
		cout << setw(20) << setfill(' ') << left << phone_title;
		cout << setw(20) << setfill(' ') << left << job_title << endl;
	}

	void display() {
		title();
		for (int i = 0; i < MAX_SIZE; ++i) {
			if (vis[i])
				mp[i].display();
		}
	}
};