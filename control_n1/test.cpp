#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream>
#include "test.h"
#include "select.h"
#include "Patient.h"
#include "fileReader.h"

using namespace std;
using namespace hospital;
using namespace reader;
using namespace selectFunc;

enum {
	numberOfTest = 5, sizeOfTestFile = 3
};


template<typename T, typename U>
void printInvalid(T received, U expected, string message) {
	cout << message << endl;
	cout << "Ожидалось: " << expected << endl << "Было получено: " << received << endl;
}

void fillingDataForTest(Patient** patients) {
	string surname[numberOfTest] = {
		"Roeva",
		"Ik",
		"Kjoi",
		"Uifa",
		"Yhio"
	};
	string name[numberOfTest] = {
		"Alena",
		"Ily",
		"I3",
		"IYiiiYI",
		"Poopt"
	};
	string patronymic[numberOfTest] = {
		"Olegovna",
		"Uyyy", 
		"Kjjj",
		"Piii",
		"Oiii"
	};
	string address[numberOfTest] = {
		"ylitsa 12",
		"ylitsa 14",
		"ylitsa 16",
		"ylitsa 18",
		"ylitsa 20"
	};
	int number[numberOfTest] = {
		1299,
		879,
		765,
		1233,
		8766
	};
	string diagnosis[numberOfTest] = {
		"depression",
		"prl",
		"sdvg",
		"sad", 
		"help"
	};

	for (int i = 0; i < numberOfTest; i++) {
		(*patients)[i].setSurname(surname[i]);
		(*patients)[i].setName(name[i]);
		(*patients)[i].setPatronymic(patronymic[i]);
		(*patients)[i].setAdress(address[i]);
		(*patients)[i].setNum(number[i]);
		(*patients)[i].setDiagnosis(diagnosis[i]);
	}

}

void creatingFileForTest() {
	ofstream out("test1.txt");
	out << "Roeva;Alena;Olegovna;Z14;78;depression" << endl;
	out << "a;b;c;d;899;age" << endl;
	out.close();

	ofstream out2("test2.txt");
	out2 << "" << endl;
	out2 << "" << endl;
	out2.close();

	ofstream out3("test3.txt");
	out3 << "abc;cde;efg;Z;1000;gh;Extra" << endl;
	out3.close();
}



bool testReadFile() {
	fileReader fr{};
	string message{};
	bool correct = true;
	Patient* patients = new Patient[numberOfTest];
	creatingFileForTest();
	int size = 0;
	stringstream buffer{};
	streambuf* old_cout_buf = cout.rdbuf(buffer.rdbuf());
	fr.implFile(&patients, &size, "test1.txt");
	cout.rdbuf(old_cout_buf);
	message = "Были не пройдены тесты на коректные данные";
	if (size != 2) {
		printInvalid(size, 2, message);
		correct = false;
	}

	delete[]patients;
	patients = nullptr;
	size = 0;
	buffer = {};
	old_cout_buf = cout.rdbuf(buffer.rdbuf());
	message = "Были не пройдены тесты на пустые строчки";
	fr.implFile(&patients, &size, "test2.txt");
	cout.rdbuf(old_cout_buf);
	if (size != 0) {
		printInvalid(size, 0, message);
		correct = false;
	}

	delete[]patients;
	patients = nullptr;
	size = 0;
	message = "Были не пройдены тесты на лишние данные";
	buffer = {};
	old_cout_buf = cout.rdbuf(buffer.rdbuf());
	fr.implFile(&patients, &size, "test3.txt");
	cout.rdbuf(old_cout_buf);
	if (size != 1) {
		printInvalid(size, 1, message);
		correct = false;
	}
	delete[]patients;
	patients = nullptr;
	
	return correct;
}
bool testFillingField() {
	bool correct = true;
	Patient* patients = new Patient[numberOfTest];
	fillingDataForTest(&patients);
	if (patients[3].getAdress() != "ylitsa 18") {
		printInvalid("ylitsa 18", patients[3].getAdress(), {});
		correct = false;
	}
	if (patients[2].getSurname() != "Kjoi") {
		printInvalid("Kjoi", patients[2].getSurname(), {});
		correct = false;
	}
	if (patients[4].getPatronymic() != "Oiii") {
		printInvalid("Oiii", patients[4].getPatronymic(), {});
		correct = false;
	}
	if (patients[1].getNum() != 879) {
		printInvalid(879, patients[1].getNum(), {});
		correct = false;
	}
	return correct;
}
bool testSelectByDiagnosis() {
	bool correct = true;
	select select;
	int upper = 0;
	int lower = 0;
	int oldSize = numberOfTest;
	int newSize = 0;
	string message{};
	Patient* patients = new Patient[numberOfTest];
	Patient* list = new Patient[numberOfTest];
	fillingDataForTest(&patients);
	patients[3].setDiagnosis("depression");
	patients[4].setDiagnosis("depression");
	newSize = select.selectByDiagnosis(&patients, &list, oldSize,"depression", true);
	if (newSize != 3) {
		printInvalid(3, newSize, message);
		correct = false;
	}
	return correct;
}
bool testSelectByNum() {
	bool correct = true;
	select select;
	int upper = 0;
	int lower = 0;
	int oldSize = numberOfTest;
	int newSize = 0;
	string message{};
	Patient* patients = new Patient[numberOfTest];
	Patient* list = new Patient[numberOfTest];
	fillingDataForTest(&patients);
	lower = 1000;
	upper = 8000;
	newSize = select.selectByNum(&patients, &list, oldSize, lower, upper, true);
	if (newSize != 2) {
		printInvalid(2, newSize, message);
		correct = false;
	}
	return correct;
}
bool testRemoveNegative() {
	bool correct = true;
	fileReader fr{};
	Patient* patients = new Patient[numberOfTest];

	fillingDataForTest(&patients);
	patients[3].setNum(-1);
	int size = numberOfTest;
	string message = "Были не пройдены тесты на отрицательные значения полей";
	fr.removeNegative(&patients, &size);
	if (size != numberOfTest - 1) {
		printInvalid(numberOfTest - 1, size, message);
		correct = false;
	}
	patients[2].setNum(-100);
	fr.removeNegative(&patients, &size);
	if (size != numberOfTest - 2) {
		printInvalid(numberOfTest - 2, size, message);
		correct = false;
	}
	patients[1].setNum(-10);
	patients[0].setNum(-1000);
	fr.removeNegative(&patients, &size);
	if (size != numberOfTest - 4) {
		printInvalid(numberOfTest - 4, size, message);
		correct = false;
	}
	return correct;
}

void test::startTest() {
	if (
		testReadFile() &&
		testRemoveNegative() &&
		testFillingField() &&
		testSelectByDiagnosis() &&
		testSelectByNum() 
		) {
		cout << "Все тесты были пройдены! " << endl;
	}
	else {

	}
}