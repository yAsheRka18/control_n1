#include "ui.h"
#include "Patient.h"
#include <iostream>
#include "fileReader.h"

using namespace UI;
using namespace std;
using namespace hospital;
using namespace reader;

template<typename T>
T getInput() {
	T userInput = 0;
	cout << "����: ";
	cin >> userInput;
	if (cin.fail()) {
		cout << "����������� ����. ���������� ��� ���" << endl;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "����: ";
			cin >> userInput;
		}
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}


int ui::getMenuVar(int lower, int upper) {
	bool inputCorrect = false;
	int in = 0;
	while (!inputCorrect) {
		in = getInt();
		if (in >= lower && in <= upper) {
			inputCorrect = true;
		}
		else {
			cout << "��� ������ ������ ����!" << endl;
		}
	}
	return in;
}

int ui::getSize() {
	bool inputCorrect = false;
	int in = 0;
	while (!inputCorrect) {
		in = getInt();
		if (in >= 1) {
			inputCorrect = true;
		}
		else {
			cout << "������ ��������������� ������! ���������� ��� ���" << endl;
		}
	}
	return in;
}

int ui::getIntField() {
	ui ui;
	bool inputCorrect = false;
	int in = 0;
	while (!inputCorrect) {
		in = ui.getInt();
		if (in >= 1) {
			inputCorrect = true;
		}
		else {
			cout << "������ ��������������� �����! ���������� ��� ���" << endl;
		}
	}
	return in;
}


int ui::getInt() {
	return getInput<int>();
}


void filling(Patient** patients, int i) {
	ui ui;
	string surname{};
	string name{};
	string patronymic{};
	string adress{};
	int number{};
	string diagnosis{};
	cout << "-----..........-----..........-----..........-----" << endl;

	cout << "������� ������� ��������" << endl;
	cout << "����: ";
	getline(cin, surname);
	(*patients)[i].setSurname(surname);

	cout << "������� ��� ��������" << endl;
	cout << "����: ";
	getline(cin, name);
	(*patients)[i].setName(name);

	cout << "������� �������� ��������" << endl;
	cout << "����: ";
	getline(cin, patronymic);
	(*patients)[i].setPatronymic(patronymic);

	cout << "������� ����� ��������" << endl;
	cout << "����: ";
	getline(cin, adress);
	(*patients)[i].setAdress(adress);

	cout << "������� ����� ����������� �����" << endl;
	number = ui.getIntField();
	(*patients)[i].setNum(number);

	cout << "������� ������� ��������" << endl;
	cout << "���� ";
	getline(cin, diagnosis);
	(*patients)[i].setDiagnosis(diagnosis);
}

bool ui::getBool() {
	return getInput<bool>();
}

void printInformOut() {
	cout << "��� ������������ ������ �������� ������ � ����" << endl;
	cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
	cout << "[1] - �� ���������� � ���������� ���������� ���������" << endl;
	cout << "[0] - ��������" << endl;
}

void outInitialDataInFile(Patient** patients, int size) {
	ui ui{};
	printInformOut();
	bool variant = ui.getBool();
	if (variant == 0) return;
	fileReader fr;
	fr.fillFile(patients, size);
}

int ui::readConsole(Patient** patients) {
	ui mUI;
	int size = 0;
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "������� ���������� ���������" << endl;
	size = mUI.getSize();
	cout << "-----..........-----..........-----..........-----" << endl;
	*patients = new Patient[size];
	for (int i = 0; i < size; i++) {
		cout << "�� ������� �������� �" << i+1 << endl;
		filling(patients, i);
		cout << "-----..........-----..........-----..........-----" << endl;
	}
	cout << "���� ��� ������� ��������! " << endl;
	outInitialDataInFile(patients, size);
	return size;
}

void printPatient(Patient** patients, int i) {
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "������� ��������: " << (*patients)[i].getSurname() << endl;
	cout << "��� ��������: " << (*patients)[i].getName() << endl;
	cout << "�������� ��������: " << (*patients)[i].getPatronymic() << endl;
	cout << "����� ��������: " << (*patients)[i].getAdress() << endl;
	cout << "����� ����� ��������: " << (*patients)[i].getNum() << endl;
	cout << "������� ��������: " << (*patients)[i].getDiagnosis() << endl;
}

void ui::outConsole(Patient** patients, int size) {
	if (size != 0 ) {
		cout << "��������� ������:" << endl;
		for (int i = 0; i < size; i++) {
			printPatient(patients, i);
		}
	}
	else {
		cout << "���������� ������ ������ �����" << endl <<endl;
		throw runtime_error("error"); //��������� ����������
	}
}