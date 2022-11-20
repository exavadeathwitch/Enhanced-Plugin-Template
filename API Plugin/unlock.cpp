#include "unlock.hpp"

#include "Main.h"

typedef signed char(__fastcall* UnlockCharacterAllType) (__int64 a1, unsigned int presetid);
UnlockCharacterAllType oUnlockCharacterAllType = (UnlockCharacterAllType)(plugin::moduleBase + 0x865D98 + 0xC00);

__int64 __fastcall ns4::unlock::sub_7FF6BFD16E3C(int a1) {
	for (int x = 0; x < 0xFFFF + 1; x++)
		oUnlockCharacterAllType((__int64)(plugin::moduleBase + 0x161FEB0), x);
	return osub_7FF6BFD16E3C(a1);
}