#pragma once
#include "Patient.h"
using namespace hospital;
namespace reader {
	class fileReader {
	public:
		int readFile(Patient**, string);
		void fillFile(Patient**, int);
		void implFile(Patient**, int*, string);
		void filling(Patient**, const char*, int );
		void removeNegative(Patient**, int*);
	};
}
