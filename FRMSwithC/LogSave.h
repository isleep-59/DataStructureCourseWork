#pragma once
#include "Log.h"

class LogSave {
private:
	Log* q;
	int head, rear, index;
	string index_title, employee_title, money_title, date_title, status_title, manager_title;

public:
	LogSave() {
		index = 1;
		q = new Log[MAX_SIZE];
		head = rear = 0;
		index_title = "报销单编号";
		employee_title = "提单人";
		money_title = "提单金额";
		date_title = "提单日期";
		status_title = "状态";
		manager_title = "处理人";
	}

	void push(Log tmp) {
		q[rear] = tmp;
		rear = (rear + 1) % MAX_SIZE;
	}

	void pop() {
		head = (head + 1) % MAX_SIZE;
	}

	bool empty() {
		return head == rear;
	}

	Log front() {
		return q[head];
	}

	void title() {
		cout << setw(20) << setfill(' ') << left << index_title;
		cout << setw(20) << setfill(' ') << left << employee_title;
		cout << setw(20) << setfill(' ') << left << money_title;
		cout << setw(20) << setfill(' ') << left << date_title;
		cout << setw(20) << setfill(' ') << left << status_title;
		cout << setw(20) << setfill(' ') << left << manager_title << endl;
	}

	void display() {
		title();
		while (!empty()) {
			Log tmp = front();
			cout << tmp.getDate().wYear << setw(4) << setfill('0') << right << index++;
			cout << setw(12) << setfill(' ') << ' ';
			tmp.display();
			pop();
		}
		head = 0;
	}
};