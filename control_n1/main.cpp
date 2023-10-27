#include <iostream>
#include <cstdlib>  
#include <locale>
#include "fileReader.h"
#include "Patient.h"
#include "ui.h"
#include "select.h"
#include "test.h"

using namespace UI;
using namespace reader;
using namespace selectFunc;
using namespace hospital;

enum { task1 = 1, task2 = 2, returnp = 3 };
enum { exitp = 0, rfile = 1, rconsole = 2, unitTest = 3};
enum { fileOutput = 0, coutput = 1};

void outGretting() {
    cout << "����� ���������� � ���������� ���������� ����������� ������ �1" << endl;
}

void printInputWays() {

    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� �� ������ ��������� ������ ��� �� ������ ��������� ��������� ����� ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "[1] - ���� ������ ����� ������ �� �����" << endl;
    cout << "[2] - ���� ������ ������ ������ � �������" << endl;
    cout << "[3] - ���� ������ ��������� ��������� �����" << endl;
    cout << "[0] - ���� ������ �����! �� ��������!" << endl << endl;
}

void printAction() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� ������ ������� � ������� ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "[0] - �������� ������ ��������� � ������ ��������" << endl;
    cout << "[1] - �������� ������ ��������� ����� ��� ����� ������� ��������� � �������� ���������" << endl;
}

void printOutputWays() {
    cout << "-----..........-----..........-----..........-----" << endl;
    cout << "���������� ��������, ��� �� ������ �������� ������ ?" << endl;
    cout << "����������� ������ ���� ��� ��������� � ���������, ������� :" << endl;
    cout << "[0] - ���� ������ ������� ������ � ����" << endl;
    cout << "[1] - ���� ������ ������� ������ � �������" << endl;
}

void selectImplTask(int variant, Patient** patients, Patient** list, int* size, int* newSize) {
    select selected;
    if (variant == 0) {
        *newSize = selected.selectByDiagnosis(patients, list, *size, {}, false);
    }
    if (variant == 1) {
        *newSize = selected.selectByNum(patients, list, *size, 0, 0, false);
    }
}

void selectInput(int variant, Patient** patients, int* size) {
    ui mUI;
    fileReader mReader;
    test mTest;
    switch (variant)
    {
    case exitp:
        cout << "�� ����� !" << endl;
        break;
    case rfile:
        *size = mReader.readFile(patients, {});
        break;
    case rconsole:
        *size = mUI.readConsole(patients);
        break;
    case unitTest: 
        mTest.startTest();
        break;
    }
}

void selectOutput(int variant, Patient** list, int size) {
    ui mUI;
    fileReader mReader;
    if (variant == 0) {
        mReader.fillFile(list, size);
    }
    if (variant == 1) {
        mUI.outConsole(list, size);
    }
}

void launchMenu() {
    ui mUI;
    int variant = 0;
    int boardMenu = unitTest;
    int newSize = 0;
    int size = 0;
    Patient* patients = nullptr;
    Patient* list = nullptr;
    do
    {
        printInputWays();
        variant = mUI.getMenuVar(exitp, unitTest);
        try {
            selectInput(variant, &patients, &size);
        }
        catch (const exception& e) {       //������������� ���������� ���� exception, ��������� � ���������� ����� try
            cout << e.what() << endl;
            continue;
        }
        if (variant == exitp) break;
        if (variant == unitTest) continue;
        
        printAction();
        variant = mUI.getBool();
        try {
            selectImplTask(variant, &patients, &list, &size, &newSize);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            continue;
        }
        if (variant == returnp) break;
        printOutputWays();
        boardMenu = returnp;
        variant = mUI.getBool();
        try {
            selectOutput(variant, &list, newSize);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            continue;
        }
        variant = 1;
        delete[]patients;
        patients = nullptr;
    } while (variant != exitp);
}


int main() {
    system("chcp 1251");
    outGretting();
	launchMenu();
	system("pause");
}
