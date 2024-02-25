#pragma once
#include "Log.h"

class LogQueue {
private:
	Log* q;
	int head, rear, index;

public:
	LogQueue() {
		q = new Log[MAX_SIZE];
		head = rear = 0;
		index = 1;
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
};