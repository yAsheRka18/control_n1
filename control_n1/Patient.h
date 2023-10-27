#pragma once
#pragma once
#include <string>
using namespace std;
namespace hospital {
	class Patient
	{
	public:
		string getSurname() const;
		void setSurname(string);

		string getName() const;
		void setName(string);

		string getPatronymic() const;
		void setPatronymic(string);

		string getAdress() const;
		void setAdress(string);

		int getNum() const;
		void setNum(int);

		string getDiagnosis() const;
		void setDiagnosis(string);

		bool isNegavive() const {
			return number <= 0 || surname.empty() ||
				name.empty() || patronymic.empty() ||
				adress.empty() || diagnosis.empty();
		}


	private:
		string surname{};
		string name{};
		string patronymic{};
		string adress{};
		int number{};
		string diagnosis{};


	};
}
