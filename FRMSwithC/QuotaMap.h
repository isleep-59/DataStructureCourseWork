#pragma once
#include "Quota.h"

class QuotaMap {
private:
	bool vis[MAX_SIZE];
	Quota mp[MAX_SIZE];
	string number_title, job_title, limits_title;

public:
	QuotaMap() {
		freopen("quota.txt", "r", stdin);

		memset(vis, 0, sizeof(vis));
		string number, job;
		int limits;
		cin >> number_title >> job_title >> limits_title;
		while (cin >> number >> job >> limits) {
			Quota tmp(number, job, limits);
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

	bool add(Quota tmp) {
		int idx = stoi(tmp.getNumber());
		if (!vis[idx])
			vis[idx] = true;
		else
			return false;
		mp[idx] = tmp;
		return true;
	}

	bool del(string number) {
		int idx = stoi(number);
		if (vis[idx])
			vis[idx] = false;
		else
			return false;
		return true;
	}

	bool modify(string number, Quota tmp) {
		if (!del(number))
			return false;
		add(tmp);
		return true;
	}

	Quota query(int idx) {
		return mp[idx];
	}

	void title() {
		cout << setw(20) << setfill(' ') << left << number_title;
		cout << setw(20) << setfill(' ') << left << job_title;
		cout << setw(20) << setfill(' ') << left << limits_title << endl;
	}

	void display() {
		title();
		for (int i = 0; i < MAX_SIZE; ++i) {
			if (vis[i])
				mp[i].display();
		}
	}
};