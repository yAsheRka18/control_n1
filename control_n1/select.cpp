#include <iostream>
#include "ui.h"
#include "Patient.h"
#include "select.h"
#include <string>
#include <cstring>


using namespace std;
using namespace UI;
using namespace hospital;
using namespace selectFunc;


static string byDiagnosis = "input diagnosis";
static string byRangeLow = "input lower";
static string byRangeUpper = "input upper";

void printInputInfo(string way) {
	if (way == byDiagnosis) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "������� �������, ����� �������� ������ ���������, ������� ����� ���" << endl;
		cout << "����: ";
	}
	if (way == byRangeLow) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "������� �������� ��������, ����� �������� ������ ���������, ����� ����������� ����� ������� ��������� � �������� ���������." << endl;
		cout << "������� ������ ������� ���������" << endl;
	}
	if (way == byRangeUpper) {
		cout << "-----..........-----..........-----..........-----" << endl;
		cout << "������� ������� ������� ���������" << endl;
	}
}


int select::selectByDiagnosis(Patient** patients, Patient** list, int size, string myDiagnosis, bool isTest) {
	int i = 0;
	int iter = 0;
	*list = new Patient[size];
	if(!isTest){
		printInputInfo(byDiagnosis);
		getline(cin, myDiagnosis);
	}
	for (; i < size; i++) {
		if ((*patients)[i].getDiagnosis() == myDiagnosis) {
			(*list)[iter] = (*patients)[i];
			iter++;
		}
	}
	return iter;
}

int select::selectByNum(Patient** patients, Patient** sortList, int size, int lower, int upper, bool isTest) {
	ui mUI;
	int i = 0;
	int iter = 0;
	*sortList = new Patient[size];
	if(!isTest){
		printInputInfo(byRangeLow);
		lower = mUI.getIntField();
		printInputInfo(byRangeUpper);
		upper = mUI.getIntField();
	}
	for (; i < size; i++) {
		int num = (*patients)[i].getNum();
		if ( num >= lower  && num <= upper) {
			(*sortList)[iter] = (*patients)[i];
			iter++;
		}
	}
	return iter;
}
