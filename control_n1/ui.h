#pragma once
#include "Patient.h"
using namespace hospital;

namespace UI {
	class ui 
	{
	public:
		int getInt();
		int getMenuVar(int, int);
		int getSize();
		bool getBool();
		int getIntField();
		double getDoubleField();
		int readConsole(Patient**);
		void outConsole(Patient**, int);
	};
}

