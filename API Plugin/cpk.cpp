#include "cpk.h"

#include "Main.h"

#include <iostream>

struct cpkdata
{
	const char* path;
	__int64 priority;
};

int cpk::loadCpkInitial() {
	const auto retval = CPK();


	// LOAD CUSTOM CPK
	cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));

	for (int x = 0; x < CpkToLoad.size(); x++)
	{
		unsigned int GameVersion = CpkPriority.at(x);
		std::cout << "Loaded cpk " << CpkToLoad.at(x) << std::endl;
		c->path = CpkToLoad.at(x).c_str();
		c->priority = 0;

		typedef signed __int64(__fastcall* sub_14056C3D4)(__int64 a, __int64 b);
		sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(plugin::moduleBase + 0x63D768 + 0xC00);
		sub_14056C3D4_f((__int64)c, GameVersion);
	}
	return retval;
}