#pragma once
#include <vector>
#include <string>
#include <fstream>

typedef signed int(__fastcall* c)();
inline c CPK = NULL;
inline std::vector<std::string> CpkToLoad;
inline std::vector<int> CpkPriority;
class cpk {
public:
	static int loadCpkInitial();
};