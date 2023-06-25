#pragma once
#include <vector>
#include <string>
#include <fstream>

inline std::vector<int> partnerfunction;
inline std::vector<int> partnercode;
inline std::vector<int> charfunction;
inline std::vector<int> charcodes;
typedef __int64(__fastcall* gpi)(__int64 player, int charcode);
inline gpi gpio;
typedef __int64(__fastcall* c)(int characterNum, int a2);
inline c co;
class condition {
public:
	static void ReadPartnerSlotParam(std::string _file);
	static void ReadSpecialConditionParam(std::string _file);
	static __int64 __fastcall CreatePartner(__int64 player, int partnercharcode);
	static __int64 __fastcall Create(int characterNum, int a2);
};