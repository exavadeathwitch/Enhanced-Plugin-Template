#pragma once
#include <vector>
#include <string>
#include <fstream>

inline std::vector<std::string> MessageID;
inline std::vector<std::string> MessageStr;
inline char ViewMessageConversions = 0;
typedef __int64(__fastcall* m)(__int64 MessageToDecode);
inline m g_MessageToString;
typedef __int64(__fastcall* m2)(__int64 MessageToDecode);
inline m2 g_MessageToString2;
class message {
public:
	static std::vector<std::string> ReadMessageFile(std::string _file);
	static uintptr_t Hook_MsgToString(uintptr_t MessageToDecode);
	static uintptr_t Hook_MsgToString_Alt(uintptr_t MessageToDecode);
};