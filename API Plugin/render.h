#ifndef RENDER_H
#define RENDER_H
#pragma once
#endif

typedef void(__fastcall* sub_14088E6A0) (__int64 a1, __int64 a2, __int64 a3);
inline sub_14088E6A0 osub_14088E6A0;

typedef __int64(__fastcall* sub_14089ADE0) (__int64 a1, __int64 a2);
inline sub_14089ADE0 osub_14089ADE0;

typedef __int64(__fastcall* sub_1409DFC50) (__int64* a1, __int64 a2);
inline sub_1409DFC50 osub_1409DFC50;

namespace render {
	inline bool hudon = 1;
	int __fastcall renderElements(__int64 a1, signed __int64 a2, unsigned int a3, int a4);
	void __fastcall sub_14088E6A0(__int64 a1, __int64 a2, __int64 a3);
	__int64 __fastcall sub_14089ADE0(__int64 a1, __int64 a2);
	__int64 __fastcall sub_1409DFC50(__int64* a1, __int64 a2);
	__int64 __fastcall sub_1409E1EE0(__int64 a1, __int64 a2);
}