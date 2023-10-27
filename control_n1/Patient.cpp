#include "Patient.h"
using namespace hospital;

string Patient::getSurname() const {
	return Patient::surname;
}
void Patient::setSurname(string newSurname) {
	surname = newSurname;
}

string Patient::getName() const {
	return Patient::name;
}
void Patient::setName(string newName) {
	name = newName;
}

string Patient::getPatronymic() const {
	return Patient::patronymic;
}
void Patient::setPatronymic(string newPatronymic) {
	patronymic = newPatronymic;
}

string Patient::getAdress() const {
	return Patient::adress;
}
void Patient::setAdress(string newAdress) {
	adress = newAdress;
}

int Patient::getNum() const {
	return Patient::number;
}
void Patient::setNum(int newNum) {
	number = newNum;
}

string Patient::getDiagnosis() const {
	return Patient::diagnosis;
}
void Patient::setDiagnosis(string newDiagnosis) {
	diagnosis = newDiagnosis;
}
