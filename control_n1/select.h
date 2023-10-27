#pragma once
#include "Patient.h"
using namespace hospital;
namespace selectFunc {
	class select {
	public:
		int selectByDiagnosis(Patient**, Patient**, int, string, bool);
		int selectByNum(Patient**, Patient**, int, int, int, bool);
	};
}