#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <locale>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;

typedef struct {
	map<string, vector<int>> integer;
	map<string, vector<string>> str;
	map<string, vector<double>> doub;
	map<string, vector<string>> link;
	map<string, bool> boo;
} Atrib;

template <typename Map>
bool map_comp(Map const &a, Map const &b) {
	return a.size() == b.size() && equal(a.begin(), a.end(), b.begin());
}

bool Atrib_comp(Atrib const &a, Atrib const &b) {
	bool ret = true;
	if (map_comp(a.integer, b.integer) == false)
		ret = false;

	if (map_comp(a.str, b.str) == false)
		ret = false;

	if (map_comp(a.doub, b.doub) == false)
		ret = false;

	if (map_comp(a.boo, b.boo) == false)
		ret = false;

	if (map_comp(a.link, b.link) == false)
		ret = false;

	return ret;
}

int Atrib_size(Atrib atr) {
	int size = 0;
	size += atr.integer.size();
	size += atr.str.size();
	size += atr.doub.size();
	size += atr.link.size();
	size += atr.boo.size();
	return size;
}

bool find_Atrib(Atrib atr, string name, int type) {
	bool find = false;
	switch (type) {

	case 1:
		if (atr.integer.find(name) == atr.integer.end()) {
			find = true;
		}
		break;

	case 2:
		if (atr.str.find(name) == atr.str.end()) {
			find = true;
		}
		break;

	case 3:
		if (atr.doub.find(name) == atr.doub.end()) {
			find = true;
		}
		break;

	case 4:
		if (atr.boo.find(name) == atr.boo.end()) {
			find = true;
		}
		break;

	case 5:
		if (atr.link.find(name) == atr.link.end()) {
			find = true;
		}
		break;

	case 6:
		if (atr.integer.find(name) == atr.integer.end())
			find = true;
		if (atr.str.find(name) == atr.str.end())
			find = true;
		if (atr.doub.find(name) == atr.doub.end())
			find = true;
		if (atr.boo.find(name) == atr.boo.end())
			find = true;
		if (atr.link.find(name) == atr.link.end())
			find = true;
		break;
	}
	return find;
}

typedef struct {
	map<string, Atrib> slot;
} Slot;

typedef struct {
	map<string, Slot> frame;
	map <int, Slot> proto;
} Model;

void Show_slot(Slot slot) {
	for (auto it = slot.slot.begin(); it != slot.slot.end(); ++it) {
		cout << "{ " << it->first << ": "; // ��� �����
		auto dat = it->second; // ������ �����

		for (auto ite = dat.integer.begin(); ite != dat.integer.end(); ++ite) {
			cout << "[ " << ite->first << ": "; // ��� ��������
			auto data = ite->second; // ������ ��������
			for (auto iter = data.begin(); iter != data.end(); ++iter) {
				cout << *iter << "; ";
			}
			cout << "]; ";
		}

		for (auto ite = dat.str.begin(); ite != dat.str.end(); ++ite) {
			cout << "[ " << ite->first << ": "; // ��� ��������
			auto data = ite->second; // ������ ��������
			for (auto iter = data.begin(); iter != data.end(); ++iter) {
				cout << *iter << "; ";
			}
			cout << "]; ";
		}

		for (auto ite = dat.doub.begin(); ite != dat.doub.end(); ++ite) {
			cout << "[ " << ite->first << ": "; // ��� ��������
			auto data = ite->second; // ������ ��������
			for (auto iter = data.begin(); iter != data.end(); ++iter) {
				cout << *iter << "; ";
			}
			cout << "]; ";
		}

		for (auto ite = dat.boo.begin(); ite != dat.boo.end(); ++ite) {
			cout << "[ " << ite->first << ": ] ";
		}

		for (auto ite = dat.link.begin(); ite != dat.link.end(); ++ite) {
			cout << "[ " << ite->first << ": "; // ��� ��������
			auto data = ite->second; // ������ ��������
			for (auto iter = data.begin(); iter != data.end(); ++iter) {
				cout << *iter << "; ";
			}
			cout << "]; ";
		}
		cout << "}; ";
	}
}

void show_one_frame(Model model, string frame_name, int num) {
	if (num == -1) { // ����������
		auto i = model.frame.find(frame_name);
		cout << i->first << ": " << "( "; // ��� ������
		auto da = i->second; // ������ ������
		Show_slot(da);
		cout << " )\n";
	}
	else if (num >= 0) { // ���������
		auto i = model.proto[num];
		cout << num+1 << ": " << "( "; // ����� ������
		Show_slot(i);
		cout << " )\n";
	}
}

void add_frame(Model* model) {
	int _int, tmp;
	Slot data;
	string name;
	bool find, end;
	do {
		end = false;
		cout << "1) �������� ������ �����\n";
		cout << "2) �������� ����� �� ���������\n";
		cout << "3) �������� �������� ������\n";
		cout << "������� �������: ";
		cin >> _int;
		cin.get();
	} while (_int <=0 || _int >= 4);

	if (_int == 1) {
		do {
			find = false;
			cout << "������� ��� ������ ��� ����������: ";
			cin >> name;
			cin.clear();
			cin.sync();
			auto it = model->frame.find(name);
			if (it != model->frame.end()) {
				cout << "����� � ����� ������ ��� ����������, ��������� ����\n";
				find = true;
			}
		} while (find == true);
		cout << "����� ��������\n\n";
		model->frame.emplace(piecewise_construct, make_tuple(name), make_tuple());
	}

	else if(_int == 2) {
		cout << "\n";
		for (auto it = model->proto.begin(); it != model->proto.end(); ++it) { // ����� ������� ����������
			show_one_frame(*model, "", it->first);
		}
		cout << "\n";

		do {
			cout << "������� ����� ������ ���������: ";
			cin >> tmp;
			cin.get();
			cin.clear();
			cin.sync();
		} while (tmp <= 0 || tmp > model->proto.size());
		tmp--;

		do {
			find = false;
			cout << "������� ��� ������ ��� ����������: ";
			cin >> name;
			cin.clear();
			cin.sync();
			auto it = model->frame.find(name);
			if (it != model->frame.end()) {
				cout << "����� � ����� ������ ��� ����������, ��������� ����\n";
				find = true;
			}
		} while (find == true);

		data = model->proto[tmp];
		model->frame.emplace(name, data);
	}

	else if (_int == 3) {
		int slot_count, atr_count;
		string name1, name2;

		do {
			cout << "������� ���������� ������: ";
			cin >> slot_count;
			cin.get();
			cin.clear();
			cin.sync();
		} while (slot_count <= 0);

		for (auto i = 0; i < slot_count; i++) {
			cout << "������� ��� ����� �" << i+1 << ": ";
			cin >> name1;
			cin.clear();
			cin.sync();
			cout << "������� ���������� ��������� � ����� �" << i + 1 << ": ";
			cin >> atr_count;
			cin.get();
			cin.clear();
			cin.sync();

			for (auto j = 0; j < atr_count; j++) {
				cout << "������� ��� �������� �" << j+1 << ": ";
				cin >> name2;
				cin.clear();
				cin.sync();
				do {
					cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
					cin >> tmp;
					cin.get();
					cin.clear();
					cin.sync();
					if (tmp <= 0 || tmp >= 6)
						cout << "������� �������� ��������, ��������� �������\n";
				} while (tmp <= 0 || tmp >= 6);
				
				switch (tmp) {

				case 1:
					data.slot[name1].integer.emplace(piecewise_construct, make_tuple(name2), make_tuple());
					break;

				case 2:
					data.slot[name1].str.emplace(piecewise_construct, make_tuple(name2), make_tuple());
					break;

				case 3:
					data.slot[name1].doub.emplace(piecewise_construct, make_tuple(name2), make_tuple());
					break;

				case 4:
					data.slot[name1].boo.emplace(piecewise_construct, make_tuple(name2), make_tuple());
					break;

				case 5:
					data.slot[name1].link.emplace(piecewise_construct, make_tuple(name2), make_tuple());
					break;

				}
			}
		}

		int _pro_size = model->proto.size();
		model->proto.emplace(_pro_size, data);
		cout << "\n";

	}
}

void delete_frame(Model* model) {
	string name;
	bool find;
	if (model->frame.size() > 0) {
		do {
			find = false;
			cout << "������� ��� ������ ��� ��������: ";
			cin >> name;
			cin.clear();
			cin.sync();
			auto it = model->frame.find(name);
			if (it == model->frame.end()) {
				cout << "����� � ����� ������ �� ������, ��������� ����\n";
				find = true;
			}
		} while (find == true);
		cout << "����� ������\n\n";
		model->frame.erase(name);
	}
	else
		cout << "� ���� ������ ��� �������\n\n";
}

void edit_frame(Model* model) {
	Slot data;
	string name1, name2;
	bool find;
	if (model->frame.size() > 0) {
		do {
			find = false;
			cout << "������� ��� ������ ��� ��������������: ";
			cin >> name1;
			cin.clear();
			cin.sync();			auto it = model->frame.find(name1);
			if (it == model->frame.end()) {
				cout << "����� � ����� ������ �� ������, ��������� ����\n";
				find = true;
			}
		} while (find == true);

		do {
			find = false;
			cout << "������� ����� ������: ";
			cin >> name2;
			cin.clear();
			cin.sync();			auto it = model->frame.find(name2);
			if (it != model->frame.end()) {
				cout << "����� � ����� ������ ��� ����������, ��������� ����\n";
				find = true;
			}
		} while (find == true);

		data = model->frame.find(name1)->second;
		model->frame.erase(name1);
		model->frame.emplace(name2, data);

		cout << "����� �������\n\n";
	}
	else
		cout << "� ���� ������ ��� �������\n\n";
}

void add_slot(Model* model) {
	Slot data;
	int i;
	string s;
	double d;
	string link;
	bool b;

	int type;
	bool end, find;
	string slot, name, atr;

	if (model->frame.size() > 0) {
		do {
			find = false;
			cout << "������� ��� ������: ";
			cin >> name;
			cin.clear();
			cin.sync();
			auto it = model->frame.find(name);
			if (it == model->frame.end()) {
				cout << "����� � ����� ������ �� ������, ��������� ����\n";
				find = true;
			}
		} while (find == true);

		cout << "������� ��� �����: ";
		cin >> slot;
		cin.clear();
		cin.sync();

		cout << "������� ��� ��������: ";
		cin >> atr;
		cin.clear();
		cin.sync();

		do {
			end = false;
			cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
			cin >> type;
			cin.get();
			cin.clear();
			cin.sync();			if (type >= 1 && type <= 4)
				end = true;
			else {
				cout << "������ �������� ����� ����, ��������� ����\n";
			}
		} while (end == false);

		cout << "������� �������� ��������: ";

		switch (type) {

		case 1:
			cin >> i;
			cin.get();
			cin.clear();
			cin.sync();
			cout << "\n";
			if (model->frame[name].slot.find(slot) == model->frame[name].slot.end()) { // ���� ���� �� ����������
				model->frame[name].slot.emplace(piecewise_construct, make_tuple(slot), make_tuple());
			}
			if (model->frame[name].slot[slot].integer.find(atr) == model->frame[name].slot[slot].integer.end()) // ���� �� ������ �������
				model->frame[name].slot[slot].integer.emplace(piecewise_construct, make_tuple(atr), make_tuple());
			model->frame[name].slot[slot].integer[atr].push_back(i);
			break;

		case 2:
			cin >> s;
			cin.clear();
			cin.sync();			cout << "\n";
			if (model->frame[name].slot.find(slot) == model->frame[name].slot.end()) { // ���� ���� �� ����������
				model->frame[name].slot.emplace(piecewise_construct, make_tuple(slot), make_tuple());
			}
			if (model->frame[name].slot[slot].str.find(atr) == model->frame[name].slot[slot].str.end()) // ���� �� ������ �������
				model->frame[name].slot[slot].str.emplace(piecewise_construct, make_tuple(atr), make_tuple());
			model->frame[name].slot[slot].str[atr].push_back(s);
			break;

		case 3:
			cin >> d;
			cin.get();
			cin.clear();
			cin.sync();			cout << "\n";
			if (model->frame[name].slot.find(slot) == model->frame[name].slot.end()) { // ���� ���� �� ����������
				model->frame[name].slot.emplace(piecewise_construct, make_tuple(slot), make_tuple());
			}
			if (model->frame[name].slot[slot].doub.find(atr) == model->frame[name].slot[slot].doub.end()) // ���� �� ������ �������
				model->frame[name].slot[slot].doub.emplace(piecewise_construct, make_tuple(atr), make_tuple());
			model->frame[name].slot[slot].doub[atr].push_back(d);
			break;

		case 4:
			do {
				cout << "0 - false, 1 - true\n";
				cin >> i;
				cin.get();
				cin.clear();
				cin.sync();				if (i < 0 || i > 1)
					cout << "������� �������� ��������, ��������� �������\n";
			} while (i < 0 || i > 1);
			if (i == 0)
				b = false;
			else
				b = true;
			cout << "\n";
			if (model->frame[name].slot.find(slot) == model->frame[name].slot.end()) { // ���� ���� �� ����������
				model->frame[name].slot.emplace(piecewise_construct, make_tuple(slot), make_tuple());
			}
			if (model->frame[name].slot[slot].boo.find(atr) == model->frame[name].slot[slot].boo.end()) // ���� �� ������ �������
				model->frame[name].slot[slot].boo.emplace(piecewise_construct, make_tuple(atr), make_tuple());
			model->frame[name].slot[slot].boo[atr] = b;
			break;

		case 5:
			cin >> link;
			cin.clear();
			cin.sync();			cout << "\n";
			if (model->frame[name].slot.find(slot) == model->frame[name].slot.end()) { // ���� ���� �� ����������
				model->frame[name].slot.emplace(piecewise_construct, make_tuple(slot), make_tuple());
			}
			if (model->frame[name].slot[slot].link.find(atr) == model->frame[name].slot[slot].link.end()) // ���� �� ������ �������
				model->frame[name].slot[slot].link.emplace(piecewise_construct, make_tuple(atr), make_tuple());
			model->frame[name].slot[slot].link[atr].push_back(link);
			break;
		}
	}
	else // ��� �������
		cout << "� ���� ������ ��� �������\n\n";
}

void delete_slot(Model* model) {
	int i;
	string s, link;
	double d;
	bool b;

	vector<int>::iterator in;
	map<string, bool>::iterator bo;
	vector<string>::iterator st;
	vector<double>::iterator dob;

	int type, count_slots = 0, cmd;
	bool end, find_slot = false;
	string slot, name, atr;

	if (model->frame.size() > 0) {
		do {
			end = false;
			cout << "������� ��� ������: ";
			cin >> name;
			cin.clear();
			cin.sync();			auto it = model->frame.find(name);
			if (it == model->frame.end()) {
				cout << "����� � ����� ������ �� ������, ��������� ����\n";
				end = true;
			}
		} while (end == true);

		cout << "������� ��� �����: ";
		cin >> slot;
		cin.clear();
		cin.sync();
		do {
			end = false;
			cout << "1) ������� ����\n";
			cout << "2) ������� �������\n";
			cout << "3) ������� �������� ��������\n";
			cout << "����� �������: ";
			cin >> cmd;
			cin.get();
			cin.clear();
			cin.sync();			if (cmd <= 0 || cmd >= 4)
				cout << "������� �������� �������, ��������� ����\n";
			else
				end = true;
		} while (end == false);

		switch (cmd) {

		case 1: // �������� �����
			if (model->frame[name].slot.find(slot) != model->frame[name].slot.end()) // ���� �����
				model->frame[name].slot.erase(slot);
			else
				cout << "������ � ����� ������ �� �������\n\n";
			break;

		case 2: // �������� ��������
			cout << "������� ��� ��������: ";
			cin >> atr;
			cin.clear();
			cin.sync();			cout << "������� ��� �������� ��������: ";

			do {
				end = false;
				cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
				cin >> type;
				cin.get();
				cin.clear();
				cin.sync();				if (type >= 1 && type <= 4)
					end = true;
				else {
					cout << "������ �������� ����� ����, ��������� ����\n";
				}
			} while (end == false);

			switch (type) {

			case 1:
				if (model->frame[name].slot[slot].integer.find(atr) != model->frame[name].slot[slot].integer.end()) // ���� �������
					model->frame[name].slot[slot].integer.erase(atr);
				else
					cout << "�� ������� ������ � ��������� ������ � ������ ��������\n\n";
				break;

			case 2:
				if (model->frame[name].slot[slot].str.find(atr) != model->frame[name].slot[slot].str.end()) // ���� �������
					model->frame[name].slot[slot].str.erase(atr);
				else
					cout << "�� ������� ������ � ��������� ������ � ������ ��������\n\n";
				break;

			case 3:
				if (model->frame[name].slot[slot].doub.find(atr) != model->frame[name].slot[slot].doub.end()) // ���� �������
					model->frame[name].slot[slot].doub.erase(atr);
				else
					cout << "�� ������� ������ � ��������� ������ � ������ ��������\n\n";
				break;

			case 4:
				if (model->frame[name].slot[slot].boo.find(atr) != model->frame[name].slot[slot].boo.end()) // ���� �������
					model->frame[name].slot[slot].boo.erase(atr);
				else
					cout << "�� ������� ������ � ��������� ������ � ������ ��������\n\n";
				break;

			case 5:
				if (model->frame[name].slot[slot].link.find(atr) != model->frame[name].slot[slot].link.end()) // ���� �������
					model->frame[name].slot[slot].link.erase(atr);
				else
					cout << "�� ������� ������ � ��������� ������ � ������ ��������\n\n";
				break;
			}
			break;

		case 3: // �������� �������� ��������
			cout << "������� ��� ��������: ";
			cin >> atr;

			do {
				end = false;
				cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
				cin >> type;
				cin.get();
				cin.clear();
				cin.sync();				if (type >= 1 && type <= 4)
					end = true;
				else {
					cout << "������ �������� ����� ����, ��������� ����\n";
				}
			} while (end == false);

			switch (type) {

			case 1:
				cout << "������� �������� �������� int: ";
				cin >> i;
				cin.get();
				cin.clear();
				cin.sync();				in = find(model->frame[name].slot[slot].integer[atr].begin(), model->frame[name].slot[slot].integer[atr].end(), i);
				if (in != model->frame[name].slot[slot].integer[atr].end()) // ���� �������
					model->frame[name].slot[slot].integer[atr].erase(in);
				else
					cout << "�� ������� ������ � ��������� �����, ������ �������� � ���������\n\n";
				break;

			case 2:
				cout << "������� �������� �������� string: ";
				cin >> s;
				cin.clear();
				cin.sync();				st = find(model->frame[name].slot[slot].str[atr].begin(), model->frame[name].slot[slot].str[atr].end(), s);
				if (st != model->frame[name].slot[slot].str[atr].end()) // ���� �������
					model->frame[name].slot[slot].str[atr].erase(st);
				else
					cout << "�� ������� ������ � ��������� �����, ������ �������� � ���������\n\n";
				break;

			case 3:
				cout << "������� �������� �������� double: ";
				cin >> d;
				cin.get();
				cin.clear();
				cin.sync();				dob = find(model->frame[name].slot[slot].doub[atr].begin(), model->frame[name].slot[slot].doub[atr].end(), d);
				if (dob != model->frame[name].slot[slot].doub[atr].end()) // ���� �������
					model->frame[name].slot[slot].doub[atr].erase(dob);
				else
					cout << "�� ������� ������ � ��������� �����, ������ �������� � ���������\n\n";
				break;

			case 4:
				do {
					cout << "0 - false, 1 - true\n";
					cin >> i;
					cin.get();
					cin.clear();
					cin.sync();					if (i < 0 || i > 1)
						cout << "������� �������� ��������, ��������� �������\n\n";
				} while (i < 0 || i > 1);
				if (i == 0)
					b = false;
				else
					b = true;
				cout << "\n";
				bo = model->frame[name].slot[slot].boo.find(atr);
				if (bo->second == b) { // ���� �������
					model->frame[name].slot[slot].boo.erase(atr);
					model->frame[name].slot[slot].boo.emplace(piecewise_construct, make_tuple(atr), make_tuple());
				}
				else
					cout << "�� ������� ������ � ��������� �����, ������ �������� � ���������\n\n";
				break;

			case 5:
				cout << "������� �������� �������� string: ";
				cin >> link;
				cin.clear();
				cin.sync();
				st = find(model->frame[name].slot[slot].link[atr].begin(), model->frame[name].slot[slot].link[atr].end(), s);
				if (st != model->frame[name].slot[slot].link[atr].end()) // ���� �������
					model->frame[name].slot[slot].link[atr].erase(st);
				else
					cout << "�� ������� ������ � ��������� �����, ������ �������� � ���������\n\n";
				break;
			}
			break;
		}
	}
	else // ��� �������
		cout << "� ���� ������ ��� �������\n\n";
}

void edit_slot(Model* model) {
	int i, new_i;
	string s, link, new_s;
	double d, new_d;
	bool b, new_b;

	vector<int>::iterator in;
	vector<string>::iterator st;
	vector<double>::iterator dob;

	map<string, bool>::iterator bo;
	map<string, vector<int>>::iterator it_i;
	map<string, vector<double>>::iterator it_d;
	map<string, vector<string>>::iterator it_s;

	map<string, Atrib>::iterator iter;

	int type, count_slots = 0, cmd;
	bool end, find_slot = false;
	string slot, name, atr, new_slot_name, new_atr_name;

	if (model->frame.size() > 0) {
		do {
			end = false;
			cout << "������� ��� ������: ";
			cin >> name;
			cin.clear();
			cin.sync();			auto it = model->frame.find(name);
			if (it == model->frame.end()) {
				cout << "����� � ����� ������ �� ������, ��������� ����\n";
				end = true;
			}
		} while (end == true);

		cout << "������� ��� �����: ";
		cin >> slot;
		cin.clear();
		cin.sync();

		do {
			end = false;
			cout << "1) �������� ��� �����\n";
			cout << "2) �������� ��� ��������\n";
			cout << "3) �������� �������� ��������\n";
			cout << "����� �������: ";
			cin >> cmd;
			cin.get();
			cin.clear();
			cin.sync();
			if (cmd <= 0 || cmd >= 4)
				cout << "������� �������� �������, ��������� ����\n";
			else
				end = true;
		} while (end == false);

		switch (cmd) {

		case 1: // ��������� ����� �����
			cout << "������� ����� ��� �����:";
			cin >> new_slot_name;
			cin.clear();
			cin.sync();
			iter = model->frame[name].slot.find(slot);
			if (iter != model->frame[name].slot.end()) { // ���� �����
				model->frame[name].slot.erase(slot);
				model->frame[name].slot.emplace(piecewise_construct, make_tuple(new_slot_name), make_tuple(iter->second));
			}
			else
				cout << "������ � ����� ������ �� �������\n\n";
			break;

		case 2: // ��������� ����� ��������
			cout << "������� ��� ��������: ";
			cin >> atr;
			cin.clear();
			cin.sync();

			do {
				end = false;
				cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
				cin >> type;
				cin.get();
				cin.clear();
				cin.sync();
				if (type >= 1 && type <= 4)
					end = true;
				else {
					cout << "������ �������� ����� ����, ��������� ����\n";
				}
			} while (end == false);

			cout << "������� ����� ��� ��������: ";
			cin >> new_atr_name;
			cin.clear();
			cin.sync();

			switch (type) {

			case 1:
				it_i = model->frame[name].slot[slot].integer.find(atr);
				if (it_i != model->frame[name].slot[slot].integer.end()) { // ���� �������
					if (model->frame[name].slot[slot].integer.find(new_atr_name) == model->frame[name].slot[slot].integer.end()) // ���� �� ����������
						model->frame[name].slot[slot].integer.emplace(new_atr_name, it_i->second);
					else {
						for (auto z = it_i->second.begin(); z != it_i->second.end(); z++) {
							new_i = *z;
							model->frame[name].slot[slot].integer[new_atr_name].push_back(new_i);
						}
					}
					model->frame[name].slot[slot].integer.erase(atr);
				}
				else
					cout << "����� � ��������� ������ � ������ �������� �� ������\n\n";
				break;

			case 2:
				it_s = model->frame[name].slot[slot].str.find(atr);
				if (it_s != model->frame[name].slot[slot].str.end()) { // ���� �������
					if (model->frame[name].slot[slot].str.find(new_atr_name) == model->frame[name].slot[slot].str.end()) // ���� �� ����������
						model->frame[name].slot[slot].str.emplace(new_atr_name, it_s->second);
					else {
						for (auto z = it_s->second.begin(); z != it_s->second.end(); z++) {
							new_s = *z;
							model->frame[name].slot[slot].str[new_atr_name].push_back(new_s);
						}
					}
					model->frame[name].slot[slot].str.erase(atr);
				}
				else
					cout << "����� � ��������� ������ � ������ �������� �� ������\n\n";
				break;

			case 3:
				it_d = model->frame[name].slot[slot].doub.find(atr);
				if (it_d != model->frame[name].slot[slot].doub.end()) { // ���� �������
					if (model->frame[name].slot[slot].doub.find(new_atr_name) == model->frame[name].slot[slot].doub.end()) // ���� �� ����������
						model->frame[name].slot[slot].doub.emplace(new_atr_name, it_d->second);
					else {
						for (auto z = it_d->second.begin(); z != it_d->second.end(); z++) {
							new_d = *z;
							model->frame[name].slot[slot].doub[new_atr_name].push_back(new_d);
						}
					}
					model->frame[name].slot[slot].doub.erase(atr);
				}
				else
					cout << "����� � ��������� ������ � ������ �������� �� ������\n\n";
				break;

			case 4:
				bo = model->frame[name].slot[slot].boo.find(atr);
				if (bo != model->frame[name].slot[slot].boo.end()) { // ���� �������
					if (model->frame[name].slot[slot].boo.find(new_atr_name) == model->frame[name].slot[slot].boo.end()) // ���� �� ����������
						model->frame[name].slot[slot].boo.emplace(new_atr_name, bo->second);
					else {
						model->frame[name].slot[slot].boo[new_atr_name] = bo->second;
					}
					model->frame[name].slot[slot].boo.erase(atr);
				}
				else
					cout << "������ � ��������� ������ � ������ �������� �� ������\n\n";
				break;

			case 5:
				it_s = model->frame[name].slot[slot].link.find(atr);
				if (it_s != model->frame[name].slot[slot].link.end()) { // ���� �������
					if (model->frame[name].slot[slot].link.find(new_atr_name) == model->frame[name].slot[slot].link.end()) // ���� �� ����������
						model->frame[name].slot[slot].link.emplace(new_atr_name, it_s->second);
					else {
						for (auto z = it_s->second.begin(); z != it_s->second.end(); z++) {
							new_s = *z;
							model->frame[name].slot[slot].link[new_atr_name].push_back(new_s);
						}
					}
					model->frame[name].slot[slot].link.erase(atr);
				}
				else
					cout << "������ � ��������� ������ � ������ �������� �� ������\n\n";
				break;
			}
			break;

		case 3: // ��������� �������� ��������
			cout << "������� ��� ��������: ";
			cin >> atr;
			cin.clear();
			cin.sync();

			do {
				end = false;
				cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
				cin >> type;
				cin.get();
				cin.clear();
				cin.sync();
				if (type >= 1 && type <= 4)
					end = true;
				else {
					cout << "������ �������� ����� ����, ��������� ����\n";
				}
			} while (end == false);

			switch (type) {

			case 1:
				cout << "������� �������� �������� int: ";
				cin >> i;
				cin.get();
				cin.clear();
				cin.sync();

				cout << "������� ����� �������� �������� int: ";
				cin >> new_i;
				cin.get();
				cin.clear();
				cin.sync();

				in = find(model->frame[name].slot[slot].integer[atr].begin(), model->frame[name].slot[slot].integer[atr].end(), i);
				if (in != model->frame[name].slot[slot].integer[atr].end()) { // ���� �������
					model->frame[name].slot[slot].integer[atr].erase(in);
					model->frame[name].slot[slot].integer[atr].push_back(new_i);
				}
				else
					cout << "����� � ��������� ������, ������ �������� � ��������� �� ������\n\n";
				break;

			case 2:
				cout << "������� �������� �������� string: ";
				cin >> s;
				cin.clear();
				cin.sync();

				cout << "������� ����� �������� �������� string: ";
				cin >> new_s;
				cin.clear();
				cin.sync();

				st = find(model->frame[name].slot[slot].str[atr].begin(), model->frame[name].slot[slot].str[atr].end(), s);
				if (st != model->frame[name].slot[slot].str[atr].end()) { // ���� �������
					model->frame[name].slot[slot].str[atr].erase(st);
					model->frame[name].slot[slot].str[atr].push_back(new_s);
				}
				else
					cout << "����� � ��������� ������, ������ �������� � ��������� �� ������\n\n";
				break;

			case 3:
				cout << "������� �������� �������� double: ";
				cin >> d;
				cin.get();
				cin.clear();
				cin.sync();

				cout << "������� ����� �������� �������� double: ";
				cin >> new_d;
				cin.get();
				cin.clear();
				cin.sync();

				dob = find(model->frame[name].slot[slot].doub[atr].begin(), model->frame[name].slot[slot].doub[atr].end(), d);
				if (dob != model->frame[name].slot[slot].doub[atr].end()) {// ���� �������
					model->frame[name].slot[slot].doub[atr].erase(dob);
					model->frame[name].slot[slot].doub[atr].push_back(new_d);
				}
				else
					cout << "����� � ��������� ������, ������ �������� � ��������� �� ������\n\n";
				break;

			case 4:
				do {
					cout << "0 - false, 1 - true\n";
					cin >> i;
					cin.get();
					cin.clear();
					cin.sync();
					if (i < 0 || i > 1)
						cout << "������� �������� ��������, ��������� �������\n";
				} while (i < 0 || i > 1);
				if (i == 0)
					b = false;
				else
					b = true;
				cout << "\n";
				new_b = !b;
				bo = model->frame[name].slot[slot].boo.find(atr);
				if (bo->second == b) { // ���� �������
					model->frame[name].slot[slot].boo.erase(atr);
					model->frame[name].slot[slot].boo.emplace(piecewise_construct, make_tuple(atr), make_tuple(new_b));
				}
				else
					cout << "����� � ��������� ������, ������ �������� � ��������� �� ������\n\n";
				break;

			case 5:
				cout << "������� �������� �������� string: ";
				cin >> link;
				cin.clear();
				cin.sync();

				cout << "������� �������� �������� string: ";
				cin >> new_s;
				cin.clear();
				cin.sync();

				st = find(model->frame[name].slot[slot].link[atr].begin(), model->frame[name].slot[slot].link[atr].end(), s);
				if (st != model->frame[name].slot[slot].link[atr].end()) { // ���� �������
					model->frame[name].slot[slot].link[atr].erase(st);
					model->frame[name].slot[slot].link[atr].push_back(new_s);
				}
				else
					cout << "����� � ��������� ������, ������ �������� � ��������� �� ������\n\n";
				break;
			}
			break;
		}
	}
	else // ��� �������
		cout << "� ���� ������ ��� �������\n\n";
}

void save_file(Model model) {
	int count_slot = 0;
	ofstream file;
	string filename;

	cout << "������� ��� ����� ��� ���������� ���� ������: ";
	cin >> filename;
	cin.clear();
	cin.sync();
	file.open(filename, fstream::out);

	// ����������
	file << model.frame.size() << "\n"; // ���������� �������
	for (auto i = model.frame.begin(); i != model.frame.end(); ++i) { // ��� ������ (�� ���������)
		file << i->first << "\n"; // ��� ������
		auto da = i->second.slot; // ������ �����
		file << da.size() << "\n"; // ���������� ������
		for (auto it = da.begin(); it != da.end(); ++it) {
			file << it->first << "\n"; // ��� �����
			auto dat = it->second; // ������ �����

			//int
			file << dat.integer.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.integer.begin(); ite != dat.integer.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
				auto data = ite->second; // ������ ���������
				file << data.size() << "\n"; // ���������� �������� ���������
				for (auto iter = data.begin(); iter != data.end(); ++iter) {
					file << *iter << " ";
				}
				file << "\n";
			}

			//string
			file << dat.str.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.str.begin(); ite != dat.str.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
				auto data = ite->second; // ������ ���������
				file << data.size() << "\n"; // ���������� �������� ���������
				for (auto iter = data.begin(); iter != data.end(); ++iter) {
					file << *iter << " ";
				}
				file << "\n";
			}

			//double
			file << dat.doub.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.doub.begin(); ite != dat.doub.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
				auto data = ite->second; // ������ ���������
				file << data.size() << "\n"; // ���������� �������� ���������
				for (auto iter = data.begin(); iter != data.end(); ++iter) {
					file << *iter << " ";
				}
				file << "\n";
			}

			//bool
			file << dat.boo.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.boo.begin(); ite != dat.boo.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
				auto data = ite->second; // ������ ���������
				file << data << "\n";
			}

			//link
			file << dat.link.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.link.begin(); ite != dat.link.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
				auto data = ite->second; // ������ ���������
				file << data.size() << "\n"; // ���������� �������� ���������
				for (auto iter = data.begin(); iter != data.end(); ++iter) {
					file << *iter << " ";
				}
				file << "\n";
			}
		}
	}

	// ���������
	file << model.proto.size() << "\n"; // ���������� �������
	int _i  = 0;
	for (auto i = model.proto.begin(); i != model.proto.end(); ++i) { // ��� ������ (�� ���������)
		file << _i++ << "\n"; // ����� ������
		auto da = i->second.slot; // ������ �����
		file << da.size() << "\n"; // ���������� ������
		for (auto it = da.begin(); it != da.end(); ++it) {
			file << it->first << "\n"; // ��� �����
			auto dat = it->second; // ������ �����

			//int
			file << dat.integer.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.integer.begin(); ite != dat.integer.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
			}

			//string
			file << dat.str.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.str.begin(); ite != dat.str.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
			}

			//double
			file << dat.doub.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.doub.begin(); ite != dat.doub.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
			}

			//bool
			file << dat.boo.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.boo.begin(); ite != dat.boo.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
			}

			//link
			file << dat.link.size() << "\n"; // ���������� ��������� int
			for (auto ite = dat.link.begin(); ite != dat.link.end(); ++ite) {
				file << ite->first << "\n"; // ��� ��������
			}
		}
	}

	file.close();
}

void open_file(Model* model) {
	ifstream file;
	string filename;

	Atrib atr;
	Slot slot;

	vector<int> v_i;
	vector<string> v_s;
	vector<double> v_d;
	bool v_b;
	vector<string> v_l;

	int int_;
	double d;
	string s;

	int frame_count, slot_count, int_count, str_count, double_count, bool_count, link_count, data_count;
	string frame_name, slot_name, atr_name;

	cout << "������� ��� ����� ��� �������� ���� ������: ";
	cin >> filename;
	cin.clear();
	cin.sync();
	file.open(filename, fstream::in);
	if (file) {

		// ���������� //
		file >> frame_count; 
		file.get();
		for (int i = 0; i < frame_count; i++) {
			file >> frame_name; // ��� ������
			file >> slot_count; // ���������� ������
			file.get();
			for (int k = 0; k < slot_count; k++) {
				file >> slot_name; // ��� �����

				// int
				file >> int_count; // ���-�� ��������� � int
				file.get();
				if (int_count > 0) {
					for (int j = 0; j < int_count; j++) {
						file >> atr_name; // ��� ��������
						file >> data_count; // ���������� ��������
						file.get();
						for (int z = 0; z < data_count; z++) {
							file >> int_;
							file.get();
							v_i.push_back(int_);
						}
						atr.integer.emplace(atr_name, v_i);
						v_i.clear();
					}
				}

				//string
				file >> str_count; // ���-�� ��������� � string
				file.get();
				if (str_count > 0) {
					for (int j = 0; j < str_count; j++) {
						file >> atr_name; // ��� ��������
						file >> data_count; // ���������� ��������
						file.get();
						for (int z = 0; z < data_count; z++) {
							file >> s;
							v_s.push_back(s);
						}
						atr.str.emplace(atr_name, v_s);
						v_s.clear();
					}
				}

				// double
				file >> double_count; // ���-�� ��������� � string
				file.get();
				if (double_count > 0) {
					for (int j = 0; j < double_count; j++) {
						file >> atr_name; // ��� ��������
						file >> data_count; // ���������� ��������
						file.get();
						for (int z = 0; z < data_count; z++) {
							file >> d;
							file.get();
							v_d.push_back(d);
						}
						atr.doub.emplace(atr_name, v_d);
						v_d.clear();
					}
				}

				//bool
				file >> bool_count; // ���-�� ��������� � string
				file.get();
				if (bool_count > 0) {
					for (int j = 0; j < bool_count; j++) {
						file >> atr_name; // ��� ��������
						file >> int_;
						file.get();
						if (int_ == 0)
							v_b = false;
						else if (int_ == 1)
							v_b = true;
					}
					atr.boo.emplace(atr_name, v_b);
				}

				//link
				file >> link_count; // ���-�� ��������� � string
				file.get();
				if (link_count > 0) {
					for (int j = 0; j < link_count; j++) {
						file >> atr_name; // ��� ��������
						file >> data_count; // ���������� ��������
						file.get();
						for (int z = 0; z < data_count; z++) {
							file >> s;
							v_l.push_back(s);
						}
						atr.link.emplace(atr_name, v_l);
						v_l.clear();
					}
				}

				slot.slot.emplace(slot_name, atr);
				atr.integer.clear();
				atr.str.clear();
				atr.doub.clear();
				atr.boo.clear();
				atr.link.clear();
			}
			model->frame.emplace(frame_name, slot);
			slot.slot.clear();
		}

		// ��������� //
		int _i;
		file >> frame_count;
		file.get();
		for (int i = 0; i < frame_count; i++) {
			file >> _i; // ����� ������
			file.get();
			model->proto.emplace(piecewise_construct, make_tuple(_i), make_tuple()); // ������ �����
			file >> slot_count; // ���������� ������
			file.get();
			for (int k = 0; k < slot_count; k++) {
				file >> slot_name; // ��� �����
				model->proto[_i].slot.emplace(piecewise_construct, make_tuple(slot_name), make_tuple()); // ������ ����

				// int
				file >> int_count; // ���-�� ��������� � int
				file.get();
				if (int_count > 0) {
					for (int j = 0; j < int_count; j++) {
						file >> atr_name; // ��� ��������
						model->proto[_i].slot[slot_name].integer.emplace(piecewise_construct, make_tuple(atr_name), make_tuple());
					}
				}

				//string
				file >> str_count; // ���-�� ��������� � string
				file.get();
				if (str_count > 0) {
					for (int j = 0; j < str_count; j++) {
						file >> atr_name; // ��� ��������
						model->proto[_i].slot[slot_name].str.emplace(piecewise_construct, make_tuple(atr_name), make_tuple());
					}
				}

				// double
				file >> double_count; // ���-�� ��������� � string
				file.get();
				if (double_count > 0) {
					for (int j = 0; j < double_count; j++) {
						file >> atr_name; // ��� ��������
						model->proto[_i].slot[slot_name].doub.emplace(piecewise_construct, make_tuple(atr_name), make_tuple());
					}
				}

				//bool
				file >> bool_count; // ���-�� ��������� � bool
				file.get();
				if (bool_count > 0) {
					for (int j = 0; j < bool_count; j++) {
						file >> atr_name; // ��� ��������
						model->proto[_i].slot[slot_name].boo.emplace(piecewise_construct, make_tuple(atr_name), make_tuple());
					}
				}

				//link
				file >> link_count; // ���-�� ��������� � link
				file.get();
				if (link_count > 0) {
					for (int j = 0; j < link_count; j++) {
						file >> atr_name; // ��� ��������
						model->proto[_i].slot[slot_name].link.emplace(piecewise_construct, make_tuple(atr_name), make_tuple());
					}
				}
			}
		}

		file.close();
	}

	else {
		file.close();
		cout << "���� �� ������\n\n";
	}

}

typedef struct {
	string name;
	int type;
	Atrib a;
} sm_atr;

typedef struct {
	string name;
	vector <sm_atr> atr;
} sm_sl;


void sint_src(Model model, int type) {
	int slot_count, atr_count, tmp;
	string name;
	bool not_found;
	vector <sm_sl> sl;

	cout << "������� ���������� ������: ";
	cin >> slot_count;
	cin.get();
	cin.clear();
	cin.sync();

	sl.resize(slot_count);

	for (auto i = 0; i < slot_count; i++) {
		cout << "������� ��� �����: ";
		cin >> name;
		cin.clear();
		cin.sync();
		sl[i].name = name;
		cout << "������� ���������� ��������� � ����� �" << i+1 << ": ";
		cin >> atr_count;
		cin.get();
		cin.clear();
		cin.sync();
		sl[i].atr.resize(atr_count);

		for (auto j = 0; j < atr_count; j++) {
			cout << "������� ��� ��������: ";
			cin >> name;
			cin.clear();
			cin.sync();
			sl[i].atr[j].name = name;
			do {
				cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������, 6 - ����������� ���): ";
				cin >> tmp;
				cin.get();
				cin.clear();
				cin.sync();
				if (tmp <= 0 || tmp >= 7)
					cout << "������� �������� ��������, ��������� �������\n";
			} while (tmp <= 0 || tmp >=7);
			sl[i].atr[j].type = tmp;
		}
	}

	cout << "\n";

	for (auto it = model.frame.begin(); it != model.frame.end(); ++it) {

		if (type == 0) { // ��� ����������
			if (it->second.slot.size() >= slot_count) {
				not_found = false;
				for (auto iter = sl.begin(); iter != sl.end(); ++iter) {
					auto data = *iter;
					auto fnd = it->second.slot.find(data.name);
					if (fnd != it->second.slot.end()) { // ���� �����
						if (Atrib_size(fnd->second) >= data.atr.size()) {
							for (auto k = 0; k < data.atr.size(); k++) {
								not_found = find_Atrib(fnd->second, data.atr[k].name, data.atr[k].type);  // ���� �� ����� true
							}
						} 
					}
					else // �� ����� ����� �� ������
						not_found = true;
				} 
				if (not_found == false) {
					show_one_frame(model, it->first, -1);
				}
			}
		}

		if (type == 1) { // ������ �������
			if (it->second.slot.size() == slot_count) {
				not_found = false;
				for (auto iter = sl.begin(); iter != sl.end(); ++iter) {
					auto data = *iter;
					auto fnd = it->second.slot.find(data.name);
					if (fnd != it->second.slot.end()) { // ���� �����
						if (Atrib_size(fnd->second) == data.atr.size()) {
							for (auto k = 0; k < data.atr.size(); k++) {
								not_found = find_Atrib(fnd->second, data.atr[k].name, data.atr[k].type);  // ���� �� ����� true
							}
						}
					}
					else // �� ����� ����� �� ������
						not_found = true;
				}
				if (not_found == false) {
					show_one_frame(model, it->first, -1);
				}
			}
		}

	}
	cout << "\n";
}

void sem_src(Model model, int type) { 
	
	int slot_count, atr_count, tmp, var_count;
	bool show;
	string name;
	vector <sm_sl> sl;
	vector<vector<vector<bool>>> atr_found;

	int _int;
	double d;
	string s;
	bool b;

	cout << "������� ���������� ������: ";
	cin >> slot_count;
	cin.get();
	cin.clear();
	cin.sync();

	sl.resize(slot_count);
	atr_found.resize(slot_count);

	for (auto i = 0; i < slot_count; i++) {
		cout << "������� ���������� ��������� � ����� �" << i + 1 << ": ";
		cin >> atr_count;
		cin.get();
		cin.clear();
		cin.sync();
		sl[i].atr.resize(atr_count);
		atr_found[i].resize(atr_count);
		
		for (auto j = 0; j < atr_count; j++) {

			do {
				cout << "������� ��� �������� �������� (1 - ����� �����, 2 - ������, 3 - ������������ �����, 4 - ������ ��������, 5 - ������): ";
				cin >> tmp;
				cin.get();
				cin.clear();
				cin.sync();
				if (tmp <= 0 || tmp >= 6)
					cout << "������� �������� ��������, ��������� �������\n";
			} while (tmp <= 0 || tmp >= 6);
			
			sl[i].atr[j].type = tmp;

			if (tmp != 4) {
				do {
					cout << "������� ���������� ��������: ";
					cin >> var_count;
					cin.get();
					cin.clear();
					cin.sync();
				}
				while (var_count <= 0);
			}
			else
				var_count = 1;

			atr_found[i][j].resize(var_count);

			for (auto m = 0; m < var_count; m++) {
				atr_found[i][j][m] = false;
				name = to_string(m);
				cout << "������� �������� %" << m+1 << ": ";

				switch (tmp) {

				case 1:
					cin >> _int;
					cin.get();
					cin.clear();
					cin.sync();

					sl[i].atr[j].a.integer.emplace(piecewise_construct, make_tuple(name), make_tuple());
					sl[i].atr[j].a.integer[name].push_back(_int);
					break;

				case 2:
					cin >> s;
					cin.clear();
					cin.sync();

					sl[i].atr[j].a.str.emplace(piecewise_construct, make_tuple(name), make_tuple());
					sl[i].atr[j].a.str[name].push_back(s);
					break;

				case 3:
					cin >> d;
					cin.get();
					cin.clear();
					cin.sync();

					sl[i].atr[j].a.doub.emplace(piecewise_construct, make_tuple(name), make_tuple());
					sl[i].atr[j].a.doub[name].push_back(d);
					break;

				case 4:
					do {
						cout << "0 - false, 1 - true\n";
						cin >> _int;
						cin.get();
						cin.clear();
						cin.sync();
						if (_int < 0 || _int > 1)
							cout << "������� �������� ��������, ��������� �������\n";
					} while (_int < 0 || _int > 1);
					if (_int == 0)
						b = false;
					else
						b = true;

					sl[i].atr[j].a.boo.emplace(piecewise_construct, make_tuple(name), make_tuple());
					sl[i].atr[j].a.boo[name] = b;
					break;

				case 5:
					cin >> s;
					cin.clear();
					cin.sync();

					sl[i].atr[j].a.link.emplace(piecewise_construct, make_tuple(name), make_tuple());
					sl[i].atr[j].a.link[name].push_back(s);
					break;
				}
			}
		}
	} 

	cout << "\n";

	int z;

	
	for (auto it = model.frame.begin(); it != model.frame.end(); ++it) { // ������� ���� �������
		show = true;
		if (type == 0) { // ��� ����������
			if (it->second.slot.size() >= slot_count) {
				for (auto ite = model.frame[it->first].slot.begin(); ite != model.frame[it->first].slot.end(); ++ite) {
					auto data = ite->second;
					for (int k = 0; k < slot_count; k++) { // �������� ������� ����� �� ���������
						for (int n = 0; n < sl[k].atr.size(); n++) { // �������� ������� �������� ���������
							switch (tmp) {

							case 1:
								for (auto as = sl[k].atr[n].a.integer.begin(); as != sl[k].atr[n].a.integer.end(); ++as) {
									name = as->first;
									for (auto lk = data.integer.begin(); lk != data.integer.end(); ++lk) {
										if (data.integer[lk->first].size() >= sl[k].atr[n].a.integer[name].size()) {
											z = 0;
											for (auto iter = sl[k].atr[n].a.integer[name].begin(); iter != sl[k].atr[n].a.integer[name].end(); ++iter) { // ������� �������� ������� �������� 
												if (find(data.integer[lk->first].begin(), data.integer[lk->first].end(), *iter) != data.integer[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� !=, �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							case 2:
								for (auto as = sl[k].atr[n].a.str.begin(); as != sl[k].atr[n].a.str.end(); ++as) {
									name = as->first;
									for (auto lk = data.str.begin(); lk != data.str.end(); ++lk) {
										if (data.str[lk->first].size() >= sl[k].atr[n].a.str[name].size()) {
											z = 0;
											for (auto iter = sl[k].atr[n].a.str[name].begin(); iter != sl[k].atr[n].a.str[name].end(); ++iter) { // ������� �������� ������� �������� 
												if (find(data.str[lk->first].begin(), data.str[lk->first].end(), *iter) != data.str[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� !=, �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							case 3:
								for (auto as = sl[k].atr[n].a.doub.begin(); as != sl[k].atr[n].a.doub.end(); ++as) {
									name = as->first;
									for (auto lk = data.doub.begin(); lk != data.doub.end(); ++lk) {
										if (data.doub[lk->first].size() >= sl[k].atr[n].a.doub[name].size()) { // 
											z = 0;
											for (auto iter = sl[k].atr[n].a.doub[name].begin(); iter != sl[k].atr[n].a.doub[name].end(); ++iter) { // ������� �������� ������� �������� 
												if (find(data.doub[lk->first].begin(), data.doub[lk->first].end(), *iter) != data.doub[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� !=, �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							case 4:
								for (auto as = sl[k].atr[n].a.boo.begin(); as != sl[k].atr[n].a.boo.end(); ++as) {
									name = as->first;
									z = 0;
									for (auto lk = data.boo.begin(); lk != data.boo.end(); ++lk) {
										if (data.boo[lk->first] == sl[k].atr[n].a.boo[name]) { // ����� �������� � ����� ������ �������� ����, ���� !=, �� �����
											atr_found[k][n][z] = true;
										}
									}
								}
								break;

							case 5:
								for (auto as = sl[k].atr[n].a.link.begin(); as != sl[k].atr[n].a.link.end(); ++as) {
									name = as->first;
									for (auto lk = data.link.begin(); lk != data.link.end(); ++lk) {
										if (data.link[lk->first].size() == sl[k].atr[n].a.link[name].size()) { 
											z = 0;
											for (auto iter = sl[k].atr[n].a.link[name].begin(); iter != sl[k].atr[n].a.link[name].end(); ++iter) { // ������� �������� ������� �������� 
												if (find(data.link[lk->first].begin(), data.link[lk->first].end(), *iter) != data.link[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� ==, �� �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							}
						}
					}
				}
			}
		}

		if (type == 1) { // ������ �������
			if (it->second.slot.size() == slot_count) {
				for (auto ite = model.frame[it->first].slot.begin(); ite != model.frame[it->first].slot.end(); ++ite) {
					auto data = ite->second;
					for (int k = 0; k < slot_count; k++) { // �������� ������� ����� �� ���������
						for (int n = 0; n < sl[k].atr.size(); n++) { // �������� ������� �������� ���������
							tmp = sl[k].atr[n].type;
							name = sl[k].atr[n].name;
							switch (tmp) {

							case 1:
								for (auto as = sl[k].atr[n].a.integer.begin(); as != sl[k].atr[n].a.integer.end(); ++as) {
									name = as->first;
									for (auto lk = data.integer.begin(); lk != data.integer.end(); ++lk) {
										if (data.integer[lk->first].size() == sl[k].atr[n].a.integer[name].size()) {
											z = 0;
											for (auto iter = sl[k].atr[n].a.integer[name].begin(); iter != sl[k].atr[n].a.integer[name].end(); ++iter) { // ������� �������� ������� �������� 
												z = 0;
												if (find(data.integer[lk->first].begin(), data.integer[lk->first].end(), *iter) != data.integer[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� !=, �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							case 2:
								for (auto as = sl[k].atr[n].a.str.begin(); as != sl[k].atr[n].a.str.end(); ++as) {
									name = as->first;
									for (auto lk = data.str.begin(); lk != data.str.end(); ++lk) {
										if (data.str[lk->first].size() == sl[k].atr[n].a.str[name].size()) {
											z = 0;
											for (auto iter = sl[k].atr[n].a.str[name].begin(); iter != sl[k].atr[n].a.str[name].end(); ++iter) { // ������� �������� ������� �������� 
												if (find(data.str[lk->first].begin(), data.str[lk->first].end(), *iter) != data.str[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� ==, �� �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							case 3:
								for (auto as = sl[k].atr[n].a.doub.begin(); as != sl[k].atr[n].a.doub.end(); ++as) {
									name = as->first;
									for (auto lk = data.doub.begin(); lk != data.doub.end(); ++lk) {
										if (data.doub[lk->first].size() == sl[k].atr[n].a.doub[name].size()) { // ���� ������� ��� ��������
											for (auto iter = sl[k].atr[n].a.doub[name].begin(); iter != sl[k].atr[n].a.doub[name].end(); ++iter) { // ������� �������� ������� �������� 
												z = 0;
												if (find(data.doub[lk->first].begin(), data.doub[lk->first].end(), *iter) != data.doub[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� ==, �� �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							case 4:
								for (auto as = sl[k].atr[n].a.boo.begin(); as != sl[k].atr[n].a.boo.end(); ++as) {
									name = as->first;
									for (auto lk = data.boo.begin(); lk != data.boo.end(); ++lk) {
										if (data.boo[lk->first] == sl[k].atr[n].a.boo[name]) { // ����� �������� � ����� ������ �������� ����, ���� ==, �� �� �����
											atr_found[k][n][0] = true;
										}
									}
								}
								break;

							case 5:
								for (auto as = sl[k].atr[n].a.link.begin(); as != sl[k].atr[n].a.link.end(); ++as) {
									name = as->first;
									for (auto lk = data.link.begin(); lk != data.link.end(); ++lk) {
										if (data.link[lk->first].size() == sl[k].atr[n].a.link[name].size()) { // ���� ������� ��� ��������
											for (auto iter = sl[k].atr[n].a.link[name].begin(); iter != sl[k].atr[n].a.link[name].end(); ++iter) { // ������� �������� ������� �������� 
												z = 0;
												if (find(data.link[lk->first].begin(), data.link[lk->first].end(), *iter) != data.link[lk->first].end()) { // ����� �������� � ����� ������ �������� ����, ���� ==, �� �� �����
													atr_found[k][n][z] = true;
												}
												z++;
											}
										}
									}
								}
								break;

							}
						}
					}
				}
			}
		}

		for (int f = 0; f < atr_found.size(); f++)
			for (int g = 0; g < atr_found[f].size(); g++)
				for (int j = 0; j < atr_found[f][g].size(); j++) {
					if (atr_found[f][g][j] == false)
						show = false;
				}

		if (show == true)
			show_one_frame(model, it->first, -1);

		for (int f = 0; f < atr_found.size(); f++)
			for (int g = 0; g < atr_found[f].size(); g++)
				for (int j = 0; j < atr_found[f][g].size(); j++)
					atr_found[f][g][j] = false;

	}
	cout << "\n";
	
}

void search(Model model) {
	int cmd;
	bool end;

	do {
		end = false;
		cout << "1) �������������� ����� (""��� ����������"")\n";
		cout << "2) �������������� ����� (""������ �������"")\n";
		cout << "3) ������������� ����� (""��� ����������"")\n";
		cout << "4) ������������� ����� (""������ �������"")\n";
		cout << "����� �������: ";
		cin >> cmd;
		cin.clear();
		cin.sync();
		if (cmd <= 0 || cmd >= 5)
			cout << "������� ����������� �������, ��������� ����\n";
		else
			end = true;

	} while (end == false);


	switch (cmd) {

	case 1:
		sint_src(model, 0);
		break;

	case 2:
		sint_src(model, 1);
		break;

	case 3:
		sem_src(model, 0);
		break;

	case 4:
		sem_src(model, 1);
		break;

	}
}

void show_model(Model model) {
	if (model.frame.size() > 0) {
		for (auto i = model.frame.begin(); i != model.frame.end(); ++i) {
			show_one_frame(model, i->first, -1);
		}
		cout << "---------------------------------------------------------------------------------------------------------------\n";
	}
	else
		cout << "���� ������ �����\n\n";

	if (model.proto.size() > 0) {
		int _j = 0;
		for (auto j = model.proto.begin(); j != model.proto.end(); ++j) {
			cout << "�������� �";
			show_one_frame(model, "", _j++);
		}
		cout << "\n";
	}
	else
		cout << "\n��� ������� ����������\n\n";
}

int main() {
	int cmd;
	bool end = false;
	Model model;
	string smt;

	system("chcp 1251 >> null");
	setlocale(LC_ALL, "ru");
	do {
		cout << "1)���������� ������\n";
		cout << "2)�������� ������\n";
		cout << "3)�������������� ������\n";
		cout << "4)���������� �����\n";
		cout << "5)�������� ������ �����\n";
		cout << "6)�������������� ������ �����\n";
		cout << "7)���������� ������ � ����\n";
		cout << "8)�������� ������ �� �����\n";
		cout << "9)�����\n";
		cout << "10)����������� ������\n";
		cout << "11)�����\n";
		cout << "������� ����� �������: ";
		cin >> cmd;
		cin.get();
		cin.clear();
		cin.sync();
		cout << "\n";
		switch (cmd) {

		case 1:
			add_frame(&model);
			break;

		case 2:
			delete_frame(&model);
			break;

		case 3:
			edit_frame(&model);
			break;

		case 4:
			add_slot(&model);
			break;

		case 5:
			delete_slot(&model);
			break;

		case 6:
			edit_slot(&model);
			break;

		case 7:
			save_file(model);
			break;

		case 8:
			open_file(&model);
			break;

		case 9:
			search(model);
			break;

		case 10:
			show_model(model);
			break;

		case 11:
			end = true;
			break;

		default:
			cout << "������� ����������� �������, ��������� ����\n\n";
			break;
		}
	} while (end == false);
	return 0;
}