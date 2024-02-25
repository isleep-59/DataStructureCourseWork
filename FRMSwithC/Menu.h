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
		first[0] = "��ѡ����Ҫ���еĲ���";
		first[1] = "1. ��Ϣ����";
		first[2] = "2. ��Ϣɾ��";
		first[3] = "3. ��Ϣ����";
		first[4] = "4. ��Ϣ��ѯ";
		first[5] = "5. ��Ϣչʾ";
		first[6] = "6. ��־չʾ";
		first[7] = "7. ���뱨��";
		first[8] = "8. �˳�ϵͳ";
		second[0] = "��ѡ����Ҫ�����Ķ���";
		second[1] = "1. �걨��";
		second[2] = "2. ������";
		second[3] = "3. ��ȷ���";
		second[4] = "4. �����ϲ�˵�";
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
			cout << "������";
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
					cout << "ϵͳ���˳���" << endl;
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
		cout << "���س��������ϲ�˵���" << endl;
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
			if (tmp.getStatus() == "����") {
				for (int i = 0; i < MAX_SIZE; ++i) {
					if (quota_map.check(i)) {
						Quota quota = quota_map.query(i);
						if (quota.getLimits() >= tmp.getMoney() && (quota.getJob() == "��������" || quota.getJob() == "���Ÿ�����")) {
							if (getRandom()) {
								tmp.changeStatus("��������");
							}
							else {
								tmp.changeStatus("����δͨ��");
							}
							tmp.changeManager(quota.getNumber());
							log_queue.push(tmp);
							break;
						}
					}
				}
			}
			else if (tmp.getStatus() == "��������") {
				for (int i = 0; i < MAX_SIZE; ++i) {
					if (quota_map.check(i)) {
						Quota quota = quota_map.query(i);
						if (quota.getLimits() >= tmp.getMoney() && (quota.getJob() == "��������" || quota.getJob() == "��������")) {
							if (getRandom()) {
								tmp.changeStatus("��������");
							}
							else {
								tmp.changeStatus("����δͨ��");
							}
							tmp.changeManager(quota.getNumber());
							log_queue.push(tmp);
							break;
						}
					}
				}
			}
			else if (tmp.getStatus() == "��������") {
				tmp.changeStatus("����");
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
				cout << "�������걨����Ϣ��" << endl;
				cout << "���ţ�"; cin >> number;
				cout << "������"; cin >> name;
				cout << "�ֻ��ţ�"; cin >> phone;
				Employee tmp(number, name, phone);
				tips();
				if (employee_map.add(tmp))
					cout << "��Ϣ��ӳɹ���" << endl;
				else
					cout << "��Ϣ���ʧ�ܣ������Ѵ��ڣ�" << endl;
				if (fin())
					return;
			}break;
			case 2: {
				string number, name, phone, job;
				system("cls");
				cout << "�����봦������Ϣ��" << endl;
				cout << "���ţ�"; cin >> number;
				cout << "������"; cin >> name;
				cout << "�ֻ��ţ�"; cin >> phone;
				cout << "ְλ��"; cin >> job;
				Manager tmp(number, name, phone, job);
				tips();
				if (manager_map.add(tmp))
					cout << "��Ϣ��ӳɹ���" << endl;
				else
					cout << "��Ϣ���ʧ�ܣ������Ѵ��ڣ�" << endl;
				if (fin())
					return;
			}break;
			case 3: {
				string number, job;
				int limits;
				system("cls");
				cout << "�������ȷ�����Ϣ��" << endl;
				cout << "���ţ�"; cin >> number;
				cout << "ְλ��"; cin >> job;
				cout << "����ȣ�"; cin >> limits;
				Quota tmp(number, job, limits);
				tips();
				if (quota_map.add(tmp))
					cout << "��Ϣ��ӳɹ���" << endl;
				else
					cout << "��Ϣ���ʧ�ܣ������Ѵ��ڣ�" << endl;
				if (fin())
					return;
			}break;
			}break;
		case 2:
			switch (object_status) {
			case 1: {
				string number;
				system("cls");
				cout << "�������ɾ���������˵Ĺ��ţ�"; cin >> number;
				tips();
				if (employee_map.del(number))
					cout << "��Ϣɾ���ɹ���" << endl;
				else
					cout << "��Ϣɾ��ʧ�ܣ��ù��Ų����ڣ�" << endl;
				if (fin())
					return;
			}break;
			case 2: {
				string number;
				system("cls");
				cout << "�������ɾ���Ĵ����˵Ĺ��ţ�"; cin >> number;
				tips();
				if (manager_map.del(number))
					cout << "��Ϣɾ���ɹ���" << endl;
				else
					cout << "��Ϣɾ��ʧ�ܣ��ù��Ų����ڣ�" << endl;
				if (fin())
					return;
			}break;
			case 3: {
				string number;
				system("cls");
				cout << "�������ɾ���Ķ�ȷ���Ĺ��ţ�"; cin >> number;
				tips();
				if (quota_map.del(number))
					cout << "��Ϣɾ���ɹ���" << endl;
				else
					cout << "��Ϣɾ��ʧ�ܣ��ù��Ų����ڣ�" << endl;
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
				cout << "��������޸ĵ������˵Ĺ��ţ�"; cin >> mod;
				cout << "�������޸ĺ����Ϣ��" << endl;
				cout << "���ţ�"; cin >> number;
				cout << "������"; cin >> name;
				cout << "�ֻ��ţ�"; cin >> phone;
				Employee tmp(number, name, phone);
				tips();
				if (employee_map.modify(mod, tmp))
					cout << "��Ϣ�޸ĳɹ���" << endl;
				else
					cout << "��Ϣ�޸�ʧ�ܣ��ù��Ų����ڣ�" << endl;
				if (fin())
					return;
			}break;
			case 2: {
				string mod;
				string number, name, phone, job;
				system("cls");
				cout << "��������޸ĵĴ����˵Ĺ��ţ�"; cin >> mod;
				cout << "�������޸ĺ����Ϣ��" << endl;
				cout << "���ţ�"; cin >> number;
				cout << "������"; cin >> name;
				cout << "�ֻ��ţ�"; cin >> phone;
				cout << "ְλ��"; cin >> job;
				Manager tmp(number, name, phone, job);
				tips();
				if (manager_map.modify(mod, tmp))
					cout << "��Ϣ�޸ĳɹ���" << endl;
				else
					cout << "��Ϣ�޸�ʧ�ܣ��ù��Ų����ڣ�" << endl;
				if (fin())
					return;
			}break;
			case 3: {
				string mod;
				string number, job;
				int limits;
				system("cls");
				cout << "��������޸ĵĶ�ȷ���Ĺ��ţ�"; cin >> mod;
				cout << "�������޸ĺ����Ϣ��" << endl;
				cout << "���ţ�"; cin >> number;
				cout << "ְλ��"; cin >> job;
				cout << "����ȣ�"; cin >> limits;
				Quota tmp(number, job, limits);
				tips();
				if (quota_map.modify(mod, tmp))
					cout << "��Ϣ�޸ĳɹ���" << endl;
				else
					cout << "��Ϣ�޸�ʧ�ܣ��ù��Ų����ڣ�" << endl;
				if (fin())
					return;
			}break;
			}break;
		case 4:
			switch (object_status) {
			case 1: {
				string number;
				system("cls");
				cout << "���������ѯ�������˵Ĺ��ţ�"; cin >> number;
				tips();
				int idx = stoi(number);
				if (employee_map.check(idx)) {
					Employee tmp = employee_map.query(idx);
					cout << "��Ϣ��ѯ�ɹ���" << endl;
					employee_map.title();
					tmp.display();
				}
				else {
					cout << "��Ϣ��ѯʧ�ܣ��ù��Ų����ڣ�" << endl;
				}
				if (fin())
					return;
			}break;
			case 2: {
				string number;
				system("cls");
				cout << "���������ѯ�������˵Ĺ��ţ�"; cin >> number;
				tips();
				int idx = stoi(number);
				if (manager_map.check(idx)) {
					Manager tmp = manager_map.query(idx);
					cout << "��Ϣ��ѯ�ɹ���" << endl;
					manager_map.title();
					tmp.display();
				}
				else {
					cout << "��Ϣ��ѯʧ�ܣ��ù��Ų����ڣ�" << endl;
				}
				if (fin())
					return;
			}break;
			case 3: {
				string number;
				system("cls");
				cout << "���������ѯ�������˵Ĺ��ţ�"; cin >> number;
				tips();
				int idx = stoi(number);
				if (quota_map.check(idx)) {
					Quota tmp = quota_map.query(idx);
					cout << "��Ϣ��ѯ�ɹ���" << endl;
					quota_map.title();
					tmp.display();
				}
				else {
					cout << "��Ϣ��ѯʧ�ܣ��ù��Ų����ڣ�" << endl;
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
			cout << "�����������˵Ĺ��ţ�"; cin >> number;
			int idx = stoi(number);
			cout << "�����뱨����"; cin >> money;
			Log tmp(number, money);
			log_queue.push(tmp);
			process();
			tips();
			if (employee_map.check(idx))
				cout << "��������ɹ���" << endl;
			else
				cout << "��������ʧ�ܣ��ù��Ų����ڣ�" << endl;
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