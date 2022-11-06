#include "player.h"

int __fastcall ns4::player::susanoojump(__int64 a1)
{
	int characode = *(DWORD*)(a1 + 0xC8C);
	int charindex = NULL;
	for (int i = 0; i < charlist.size(); i++) {
		if (characode == charlist[i])
			charindex = i;
	}
	if (charindex == NULL)
		return osusanoojump(a1);
	else {
		*(DWORD*)(a1 + 0xC8C) = susanoocharlist[charindex];
		auto retval = osusanoojump(a1);
		*(DWORD*)(a1 + 0xC8C) = charlist[charindex];
		return retval;
	}
}