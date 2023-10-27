#include <iostream>
#include <filesystem>
#include "fileReader.h"
#include "ui.h"
#include "Patient.h"
#include <string>
#include <fstream>
#include <cstring>


using namespace std;
using namespace reader;
using namespace UI;
using namespace hospital;

static const string mInput = "input";
static const string mOutput = "output";

enum {
	SELECT_SURNAME = 0, SELECT_NAME = 1, SELECT_PATRONYMIC = 2, SELECT_ADRESS = 3, SELECT_NUM = 4, SELECT_DIAGNOSIS = 5
};

void printInform(string way) {
	if (way == mInput) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "�������� ��������! ��� ������ �� ����� �������� ������ ���� �������� �� ����� ������ ����� ; � ��� �������� !" << endl;
		cout << "���� ������ �������� �����, ��������� ������ �� ������, ��������� ���������� � �������� ��������� �������� ����" << endl;
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "��������� ��: ";
	}
	if (way == mOutput) {
		cout << "������� �������� ����� � ������� �� ������ ��������� ���������" << endl;
	}
}

void outInform() {
	cout << "-----..........-----..........-----..........-----" << endl;
	cout << "���� ������ ���� ������� ������� �� �����!" << endl;
	cout << "�������� ��������, ��� ���� ������� ������ � �������� � ������� ��� ���������������� ������" << endl;
}

// ��������� ������ �� ���������, ��������� ������ ';' � �������� �����������
void fileReader::filling(Patient** patients, const char* str_ptr, int i) {
	int iter = 0;
	char* str_copy = new char[strlen(str_ptr) + 1];
	strcpy_s(str_copy, strlen(str_ptr) + 1, str_ptr);
	char* context = nullptr;
	char* token = strtok_s(str_copy, ";", &context);
	while (token != nullptr) {
		switch (iter) {
		case SELECT_SURNAME:
			(*patients)[i].setSurname(token);
			break;
		case SELECT_NAME :
			(*patients)[i].setName(token);
			break;
		case SELECT_PATRONYMIC:
			(*patients)[i].setPatronymic(token);
			break;
		case SELECT_ADRESS:
			(*patients)[i].setAdress(token);
			break;
		case SELECT_NUM:
			if (atoi(token) <= 0) {
				cout << "������������� ��� ������� ����� ��������! ��������� ������ � �����! � " << i + 1 << " ������" << endl;
			}
			(*patients)[i].setNum(atoi(token));
			break;
		case SELECT_DIAGNOSIS:
			(*patients)[i].setDiagnosis(token);
			break;
		default:
			cout << "������� ����� ������ � ����� ������! ������ ����� ���������������" << endl;
		}
		token = strtok_s(nullptr, ";", &context);
		iter++;
	}
	delete[] str_copy;
}


void fileReader::implFile(Patient** patients, int* size, string name) {
	int i = 0;
	string data{};
	ifstream input;
	input.open(name);
	if (input.is_open()) {
		while (getline(input, data)) {
			*size += 1;
		}
		input.close();
	}else{
		cout << endl << "����� � ����� ������ �� ����������!" << endl << endl;
		throw runtime_error("error");
	}

	input.open(name);
	if (input.is_open()) {
		*patients = new Patient[*size];
		while (getline(input, data)) {
			if (data.empty()) {
				cout << "���� �������� �� " << i+1 << " ������ �� ��� ����������! ��������� ���� � ������� ������ ������" << endl;
				*size -= 1;
			}
			else {
				filling(patients, data.c_str(), i);
			}
			i++;
		}
		input.close();
	}
	else {
		cout << endl << "������ ������ ����� ��� ��������� ������!" << endl << endl;
		throw runtime_error("An error occurred");
	}
}

void fileReader::removeNegative(Patient** patients, int* size) {
	int newSize = 0;
	for (int i = 0; i < *size; i++) {
		if (!(*patients)[i].isNegavive()) {
			(*patients)[newSize++] = (*patients)[i];
		}
	}
	// �������� ������ ��������
	for (int i = newSize; i < *size; i++) {
		(*patients)[i] = Patient();
	}
	*size = newSize;

}

int fileReader::readFile(Patient** patients, string name) {
	int size = 0;
	printInform(mInput);
	getline(cin, name);
	implFile(patients, &size, name);
	removeNegative(patients, &size);
	outInform();
	return size;
}


void fileReader::fillFile(Patient** patients, int size) {
	printInform(mOutput);
	string filePath = "";
	bool isDataSaved = false;
	ui mUI;
	do {
		cout << "��������� �:";
		getline(cin, filePath);

		if (ifstream(filePath)) {
			cout << "���� ��� ����������." << endl;
			cout << "[0] - ������������ ������������ ����." << endl;
			cout << "[1] - ��������� ����." << endl;
			int tryAnotherFile = mUI.getMenuVar(0, 1);
			if (tryAnotherFile) {
				continue;
			}
		}

		ofstream myFile(filePath, ofstream::app);     //���� ofstream::app ���������, ��� ���� ������ ���� ������ � ������ ���������� (append mode), 
														//��� ��������, ��� ���� ���� ����������, �� ������ ����� ��������� � ����� �����, � �� ������������. 
														//���� ���� �� ����������, �� �� ����� ������.

		error_code ec{};							//�������� ������ ��� �������� � ��������� ������, ������� ����� ���������� ��� ������ � �������, ������ �������� ����������

		if (!myFile) {
			cout << "������ ���������. ��������� ����." << endl;
			myFile.close();
			continue;
		}

		myFile.close();
		myFile.open(filePath, ofstream::trunc);    //trunc ��������, ��� ���� ���� ����������, �� ��� ���������� ����� ������� (�������). ���� ���� �� ����������, �� �� ����� ������
		myFile << "������\t\t���\t��������\t\t������\t����� �����\t�������\n";
		for (int i = 0; i < size; i++) {
			myFile << (*patients)[i].getSurname() << "\t\t|\t" << (*patients)[i].getName() << "\t\t|\t" << (*patients)[i].getPatronymic()
				<< "\t\t|\t" << (*patients)[i].getAdress() << "\t\t|\t" << (*patients)[i].getNum() << "\t\t|\t" << (*patients)[i].getDiagnosis() << endl;
		}
		myFile.close();
		cout << "������ ���������." << endl;
		isDataSaved = true;
	} while (!isDataSaved);
}
