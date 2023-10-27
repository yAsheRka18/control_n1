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
	cout << "Ввод: ";
	cin >> userInput;
	if (cin.fail()) {
		cout << "Некоректный ввод. Попробуйте еще раз" << endl;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Ввод: ";
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
			cout << "Нет такого пункта меню!" << endl;
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
			cout << "Введен неположительный размер! Попробуйте еще раз" << endl;
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
			cout << "Введен неположительное число! Попробуйте еще раз" << endl;
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

	cout << "Введите фамилию пациента" << endl;
	cout << "Ввод: ";
	getline(cin, surname);
	(*patients)[i].setSurname(surname);

	cout << "Введите имя пациента" << endl;
	cout << "Ввод: ";
	getline(cin, name);
	(*patients)[i].setName(name);

	cout << "Введите отчество пациента" << endl;
	cout << "Ввод: ";
	getline(cin, patronymic);
	(*patients)[i].setPatronymic(patronymic);

	cout << "Введите адрес пациента" << endl;
	cout << "Ввод: ";
	getline(cin, adress);
	(*patients)[i].setAdress(adress);

	cout << "Введите номер медицинской карты" << endl;
	number = ui.getIntField();
	(*patients)[i].setNum(number);

	cout << "Введите диагноз пациента" << endl;
	cout << "Ввод ";
	getline(cin, diagnosis);
	(*patients)[i].setDiagnosis(diagnosis);
}

bool ui::getBool() {
	return getInput<bool>();
}

void printInformOut() {
	cout << "Вам предлагается ввести исходные данные в файл" << endl;
	cout << "Используйте пункты меню для навигации в программе, нажмите :" << endl;
	cout << "[1] - Не записывать и продолжить выполнение программы" << endl;
	cout << "[0] - Записать" << endl;
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
	cout << "Введите количество пациентов" << endl;
	size = mUI.getSize();
	cout << "-----..........-----..........-----..........-----" << endl;
	*patients = new Patient[size];
	for (int i = 0; i < size; i++) {
		cout << "Вы вводите пациента №" << i+1 << endl;
		filling(patients, i);
		cout << "-----..........-----..........-----..........-----" << endl;
	}
	cout << "Ввод был успешно проведен! " << endl;
	outInitialDataInFile(patients, size);
	return size;
}

void printPatient(Patient** patients, int i) {
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "Фамилия пациента: " << (*patients)[i].getSurname() << endl;
	cout << "Имя пациента: " << (*patients)[i].getName() << endl;
	cout << "Отчество пациента: " << (*patients)[i].getPatronymic() << endl;
	cout << "Адрес пациента: " << (*patients)[i].getAdress() << endl;
	cout << "Номер карты пациента: " << (*patients)[i].getNum() << endl;
	cout << "Диагноз пациента: " << (*patients)[i].getDiagnosis() << endl;
}

void ui::outConsole(Patient** patients, int size) {
	if (size != 0 ) {
		cout << "Получение данных:" << endl;
		for (int i = 0; i < size; i++) {
			printPatient(patients, i);
		}
	}
	else {
		cout << "Попробуйте ввести данные снова" << endl <<endl;
		throw runtime_error("error"); //бросается исключение
	}
}