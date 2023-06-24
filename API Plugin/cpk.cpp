#include "cpk.h"

#include "Main.h"

#include <iostream>

struct cpkdata
{
	const char* path;
	__int64 priority;
};

int cpk::loadCpkInitial() {
	__int64 v0; // rax@1
	__int64 v1; // rbx@1
	unsigned int ActualVersion; // eax@3
	unsigned int GameVersion; // ebx@3
	__int64 v4; // rbx@5
	signed __int64 v5; // rdi@5
	const char* v6; // rax@10
	void* v7; // rdx@13
	void* v8; // rbx@16
	int v9; // eax@16
	//const char *v11; // [sp+20h] [bp-188h]@12
	//int v12; // [sp+28h] [bp-180h]@12
	void* Memory; // [sp+30h] [bp-178h]@5
	int v14; // [sp+38h] [bp-170h]@5
	const char* v15; // [sp+40h] [bp-168h]@5
	unsigned __int64 v16; // [sp+48h] [bp-160h]@5
	const char* v17; // [sp+50h] [bp-158h]@5
	int v18; // [sp+58h] [bp-150h]@5
	const char* v19; // [sp+60h] [bp-148h]@5
	int v20; // [sp+68h] [bp-140h]@5
	const char* v21; // [sp+70h] [bp-138h]@5
	int v22; // [sp+78h] [bp-130h]@5
	const char* v23; // [sp+80h] [bp-128h]@5
	int v24; // [sp+88h] [bp-120h]@5
	__int64* v25; // [sp+90h] [bp-118h]@4
	signed int v26; // [sp+98h] [bp-110h]@4
	__int64 v27; // [sp+A0h] [bp-108h]@4
	__int64 retaddr; // [sp+1A8h] [bp+0h]@1s

	v0 = (__int64)&retaddr;
	const auto retval = CPK();


	// LOAD CUSTOM CPK
	cpkdata* c = (cpkdata*)malloc(sizeof(cpkdata));

	for (int x = 0; x < CpkToLoad.size(); x++)
	{
		GameVersion = CpkPriority.at(x);
		std::cout << "Loaded cpk " << CpkToLoad.at(x) << std::endl;
		c->path = CpkToLoad.at(x).c_str();
		c->priority = 0;

		typedef signed __int64(__fastcall* sub_14056C3D4)(__int64 a, __int64 b);
		sub_14056C3D4 sub_14056C3D4_f = (sub_14056C3D4)(plugin::moduleBase + 0x56B7D4 + 0xC00);
		sub_14056C3D4_f((__int64)c, GameVersion);
	}
	return retval;
}