#pragma once
#include "Head.h"
#include "EmployeeMap.h"
#include "ManagerMap.h"
#include "QuotaMap.h"
#include "LogQueue.h"
#include "LogSave.h"
#define UP 72
#define DOWN 80

class Menu {
private:
	EmployeeMap employee_map;
	ManagerMap manager_map;
	QuotaMap quota_map;
	LogQueue log_queue;
	LogSave log_save;
	int menu_status, operation_status, object_status;
	string first[9], second[5];
	string spc, arw_r, arw_l;

public:
	Menu() :employee_map(), manager_map(), quota_map() {
		first[0] = "请选择你要进行的操作";
		first[1] = "1. 信息增加";
		first[2] = "2. 信息删除";
		first[3] = "3. 信息更改";
		first[4] = "4. 信息查询";
		first[5] = "5. 信息展示";
		first[6] = "6. 日志展示";
		first[7] = "7. 申请报销";
		first[8] = "8. 退出系统";
		second[0] = "请选择你要操作的对象";
		second[1] = "1. 申报人";
		second[2] = "2. 处理人";
		second[3] = "3. 额度分配";
		second[4] = "4. 返回上层菜单";
		spc = "          ";
		arw_r = ">>>>>>>>>>";
		arw_l = "<<<<<<<<<<";
		menu_status = 1;
		operation_status = 0;
		object_status = 0;
	}

	void display(int line) {
		system("cls");
		if(menu_status == 1)
			for (int i = 0; i < 9; ++i) {
				if (i != line)
					cout << spc << first[i] << spc << endl;
				else
					cout << arw_r << first[i] << arw_l << endl;
			}
		else if(menu_status == 2)
			for (int i = 0; i < 5; ++i) {
				if (i != line)
					cout << spc << second[i] << spc << endl;
				else
					cout << arw_r << second[i] << arw_l << endl;
			}
	}

	void tips() {
		for (int i = 0; i < 3; ++i) {
			system("cls");
			cout << "处理中";
			for (int j = 0; j < i; ++j) {
				cout << '.';
			}
			cout << endl;
			Sleep(200);
		}
		system("cls");
	}

	void read(int line) {
		char c1, c2;
		while (true) {
			display(line);

			c1 = _getch();
			if (c1 == '\r') {
				if (line == 8) {
					tips();
					cout << "系统已退出！" << endl;
					return;
				}

				if (menu_status == 1) {
					operation_status = line;
					if (line > 0 && line < 6) {
						menu_status = 2;
						read(1);
						menu_status = 1;
						continue;
					}
					else {
						operation();
						continue;
					}
				}
				else {
					object_status = line;
					operation();
					return;
				}
			}

			c2 = _getch();
			switch (c2) {
			case UP: line--; break;
			case DOWN: line++; break;
			default: continue;
			}

			if (menu_status == 1) {
				if (line > 8)
					line = 1;
				else if (line < 1)
					line = 8;
			}
			else if (menu_status == 2) {
				if (line > 4)
					line = 1;
				else if (line < 1)
					line = 4;
			}
		}
	}

	bool fin() {
		cout << "按回车键返回上层菜单！" << endl;
		char c;
		while (c = _getch()) {
			if (c == '\r')
				return true;
		}
	}

	bool getRandom() {
		srand((int)time(NULL));
		int i = rand() % 100 + 1;
		return i % 2 ? true : false;
	}

	void process() {
		while (!log_queue.empty()) {
			Log tmp = log_queue.front();
			log_queue.pop();
			log_save.push(tmp);
			if (tmp.getStatus() == "创建") {
				for (int i = 0; i < MAX_SIZE; ++i) {
					if (quota_map.check(i)) {
						Quota quota = quota_map.query(i);
						if (quota.getLimits() >= tmp.getMoney() && (quota.getJob() == "部门主管" || quota.getJob() == "部门副主管")) {
							if (getRandom()) {
								tmp.changeStatus("部门审批");
							}
							else {
								tmp.changeStatus("审批未通过");
							}
							tmp.changeManager(quota.getNumber());
							log_queue.push(tmp);
							break;
						}
					}
				}
			}
			else if (tmp.getStatus() == "部门审批") {
				for (int i = 0; i < MAX_SIZE; ++i) {
					if (quota_map.check(i)) {
						Quota quota = quota_map.query(i);
						if (quota.getLimits() >= tmp.getMoney() && (quota.getJob() == "财务主管" || quota.getJob() == "财务副主管")) {
							if (getRandom()) {
								tmp.changeStatus("财务审批");
							}
							else {
								tmp.changeStatus("审批未通过");
							}
							tmp.changeManager(quota.getNumber());
							log_queue.push(tmp);
							break;
						}
					}
				}
			}
			else if (tmp.getStatus() == "财务审批") {
				tmp.changeStatus("付款");
				log_queue.push(tmp);
			}
		}
	}

	void operation() {
		switch (operation_status) {
		case 1: 
			switch (object_status) {
			case 1: {
				string number, name, phone;
				system("cls");
				cout << "请输入申报人信息：" << endl;
				cout << "工号："; cin >> number;
				cout << "姓名："; cin >> name;
				cout << "手机号："; cin >> phone;
				Employee tmp(number, name, phone);
				tips();
				if (employee_map.add(tmp))
					cout << "信息添加成功！" << endl;
				else
					cout << "信息添加失败，工号已存在！" << endl;
				if (fin())
					return;
			}break;
			case 2: {
				string number, name, phone, job;
				system("cls");
				cout << "请输入处理人信息：" << endl;
				cout << "工号："; cin >> number;
				cout << "姓名："; cin >> name;
				cout << "手机号："; cin >> phone;
				cout << "职位："; cin >> job;
				Manager tmp(number, name, phone, job);
				tips();
				if (manager_map.add(tmp))
					cout << "信息添加成功！" << endl;
				else
					cout << "信息添加失败，工号已存在！" << endl;
				if (fin())
					return;
			}break;
			case 3: {
				string number, job;
				int limits;
				system("cls");
				cout << "请输入额度分配信息：" << endl;
				cout << "工号："; cin >> number;
				cout << "职位："; cin >> job;
				cout << "最大额度："; cin >> limits;
				Quota tmp(number, job, limits);
				tips();
				if (quota_map.add(tmp))
					cout << "信息添加成功！" << endl;
				else
					cout << "信息添加失败，工号已存在！" << endl;
				if (fin())
					return;
			}break;
			}break;
		case 2:
			switch (object_status) {
			case 1: {
				string number;
				system("cls");
				cout << "请输入待删除的申请人的工号："; cin >> number;
				tips();
				if (employee_map.del(number))
					cout << "信息删除成功！" << endl;
				else
					cout << "信息删除失败，该工号不存在！" << endl;
				if (fin())
					return;
			}break;
			case 2: {
				string number;
				system("cls");
				cout << "请输入待删除的处理人的工号："; cin >> number;
				tips();
				if (manager_map.del(number))
					cout << "信息删除成功！" << endl;
				else
					cout << "信息删除失败，该工号不存在！" << endl;
				if (fin())
					return;
			}break;
			case 3: {
				string number;
				system("cls");
				cout << "请输入待删除的额度分配的工号："; cin >> number;
				tips();
				if (quota_map.del(number))
					cout << "信息删除成功！" << endl;
				else
					cout << "信息删除失败，该工号不存在！" << endl;
				if (fin())
					return;
			}break;
			}break;
		case 3:
			switch (object_status) {
			case 1: {
				string mod;
				string number, name, phone;
				system("cls");
				cout << "请输入待修改的申请人的工号："; cin >> mod;
				cout << "请输入修改后的信息：" << endl;
				cout << "工号："; cin >> number;
				cout << "姓名："; cin >> name;
				cout << "手机号："; cin >> phone;
				Employee tmp(number, name, phone);
				tips();
				if (employee_map.modify(mod, tmp))
					cout << "信息修改成功！" << endl;
				else
					cout << "信息修改失败，该工号不存在！" << endl;
				if (fin())
					return;
			}break;
			case 2: {
				string mod;
				string number, name, phone, job;
				system("cls");
				cout << "请输入待修改的处理人的工号："; cin >> mod;
				cout << "请输入修改后的信息：" << endl;
				cout << "工号："; cin >> number;
				cout << "姓名："; cin >> name;
				cout << "手机号："; cin >> phone;
				cout << "职位："; cin >> job;
				Manager tmp(number, name, phone, job);
				tips();
				if (manager_map.modify(mod, tmp))
					cout << "信息修改成功！" << endl;
				else
					cout << "信息修改失败，该工号不存在！" << endl;
				if (fin())
					return;
			}break;
			case 3: {
				string mod;
				string number, job;
				int limits;
				system("cls");
				cout << "请输入待修改的额度分配的工号："; cin >> mod;
				cout << "请输入修改后的信息：" << endl;
				cout << "工号："; cin >> number;
				cout << "职位："; cin >> job;
				cout << "最大额度："; cin >> limits;
				Quota tmp(number, job, limits);
				tips();
				if (quota_map.modify(mod, tmp))
					cout << "信息修改成功！" << endl;
				else
					cout << "信息修改失败，该工号不存在！" << endl;
				if (fin())
					return;
			}break;
			}break;
		case 4:
			switch (object_status) {
			case 1: {
				string number;
				system("cls");
				cout << "请输入待查询的申请人的工号："; cin >> number;
				tips();
				int idx = stoi(number);
				if (employee_map.check(idx)) {
					Employee tmp = employee_map.query(idx);
					cout << "信息查询成功！" << endl;
					employee_map.title();
					tmp.display();
				}
				else {
					cout << "信息查询失败，该工号不存在！" << endl;
				}
				if (fin())
					return;
			}break;
			case 2: {
				string number;
				system("cls");
				cout << "请输入待查询的申请人的工号："; cin >> number;
				tips();
				int idx = stoi(number);
				if (manager_map.check(idx)) {
					Manager tmp = manager_map.query(idx);
					cout << "信息查询成功！" << endl;
					manager_map.title();
					tmp.display();
				}
				else {
					cout << "信息查询失败，该工号不存在！" << endl;
				}
				if (fin())
					return;
			}break;
			case 3: {
				string number;
				system("cls");
				cout << "请输入待查询的申请人的工号："; cin >> number;
				tips();
				int idx = stoi(number);
				if (quota_map.check(idx)) {
					Quota tmp = quota_map.query(idx);
					cout << "信息查询成功！" << endl;
					quota_map.title();
					tmp.display();
				}
				else {
					cout << "信息查询失败，该工号不存在！" << endl;
				}
				if (fin())
					return;
			}break;
			}break;

		case 5:
			switch (object_status) {
			case 1: {
				system("cls");
				tips();
				employee_map.display();
				if (fin())
					return;
			}break;
			case 2: {
				system("cls");
				tips();
				manager_map.display();
				if (fin())
					return;
			}break;
			case 3: {
				system("cls");
				tips();
				quota_map.display();
				if (fin())
					return;
			}break;
			}break;
		case 6: {
			system("cls");
			tips();
			log_save.display();
			if (fin())
				return;
		}break;
		case 7: {
			system("cls");
			string number;
			int money;
			cout << "请输入申请人的工号："; cin >> number;
			int idx = stoi(number);
			cout << "请输入报销金额："; cin >> money;
			Log tmp(number, money);
			log_queue.push(tmp);
			process();
			tips();
			if (employee_map.check(idx))
				cout << "报销申请成功！" << endl;
			else
				cout << "报销申请失败，该工号不存在！" << endl;
			if (fin())
				return;
		}break;
		}
	}

	void update() {
		freopen("employee.txt", "w", stdout);
		employee_map.display();
		cout.clear();
		freopen("manager.txt", "w", stdout);
		manager_map.display();
		cout.clear();
		freopen("quota.txt", "w", stdout);
		quota_map.display();
		cout.clear();
		freopen("log.txt", "w", stdout);
		log_save.display();
		cout.clear();
		freopen("CON", "w", stdout);
	}
};