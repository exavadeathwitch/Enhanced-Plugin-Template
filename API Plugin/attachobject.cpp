#include "attachobject.hpp"
inline int test = 0;

typedef signed __int64(__fastcall* getcharcode) (int a1);
getcharcode ogetcharcode = (getcharcode)(plugin::moduleBase + 0x5289FC + 0xC00);
typedef signed __int64(__fastcall* getcharcodemodel) (int a1, int a2);
getcharcodemodel ogetcharcodemodel = (getcharcodemodel)(plugin::moduleBase + 0x528B18 + 0xC00);

__int64 __fastcall ns4::attachobject::GetPlayerAttachParam(__int64 a1, int a2, const char* a3, const char* a4) {
	/*
	a.xpos = 12.0f;
	a.ypos = -9.0f;
	a.zpos = 0.0f;
	a.xrot = 180.0f;
	a.yrot = 90.0f;
	a.zrot = 0.0f;
	a.xscale = 1.0f;
	a.yscale = 1.0f;
	a.zscale = 1.0f;
	*/
	std::cout << std::hex << "num: " << a2 << std::endl;
	if (a2 == 0x6A && test == 1) {
		//std::cout << (char*)a.characodeaddr << std::endl;
		//std::cout << (char*)a.referenceboneaddr << std::endl;
		std::cout << "return\n";
		return (__int64)&grdl;//a
	}
	/*
	if (a2 == num - 1 && test == 1) {
		//std::cout << (char*)a.characodeaddr << std::endl;
		//std::cout << (char*)a.referenceboneaddr << std::endl;
		std::cout << "return2\n";
		return (__int64)&grdl;
	}
	if (a2 == num - 2 && test == 1) {
		//std::cout << (char*)a.characodeaddr << std::endl;
		//std::cout << (char*)a.referenceboneaddr << std::endl;
		std::cout << "return2\n";
		return (__int64)&grde;
	}
	if (a2 == num - 1 && test == 1) {
		//std::cout << (char*)a.characodeaddr << std::endl;
		//std::cout << (char*)a.referenceboneaddr << std::endl;
		std::cout << "return2\n";
		return (__int64)&grds;
	}*/
	auto retval = globals::hookManager->callOriginal<decltype(&ns4::attachobject::GetPlayerAttachParam)>(ns4::attachobject::GetPlayerAttachParam, a1, a2, a3, a4);
	std::cout << "retval: " << retval << std::endl;
	return retval;
}

__int64 __fastcall ns4::attachobject::GetPlayerAttachParamNum(__int64 a1, const char* a2, __int64 a3) {
	return 1;
	__int64 retval = 1 + globals::hookManager->callOriginal<decltype(&ns4::attachobject::GetPlayerAttachParamNum)>(ns4::attachobject::GetPlayerAttachParamNum, a1, a2, a3);
	return retval;
}

__int64 __fastcall ns4::attachobject::CreateAttachObject(__int64 a1, __int64 nuccXfbinDocument, const char* bod1, const char* characode) {
	if (test == 1) {
		__int64 numaddr = *(__int64*)(globals::moduleBase + 0x161C890);
		std::cout << std::hex << numaddr << std::endl;
		__int64 numaddr2 = *(__int64*)(numaddr + 0xB8);
		std::cout << std::hex << numaddr2 << std::endl;
		num = *(DWORD*)(numaddr2 + 0x20);
		std::cout << "characterload\n";
		*(DWORD*)(numaddr2 + 0x20) = num + 1;
		std::cout << std::hex << "num: " << *(DWORD*)(numaddr2 + 0x20) << std::endl;
		auto retval = globals::hookManager->callOriginal<decltype(&ns4::attachobject::CreateAttachObject)>(ns4::attachobject::CreateAttachObject, a1, nuccXfbinDocument, bod1, characode);
		std::cout << "postretval\n";
		*(DWORD*)(numaddr2 + 0x20) = num - 1;
		return retval;
	}
	return globals::hookManager->callOriginal<decltype(&ns4::attachobject::CreateAttachObject)>(ns4::attachobject::CreateAttachObject, a1, nuccXfbinDocument, bod1, characode);
}

__int64 __fastcall ns4::attachobject::DisableAttachObject(__int64 a1, int a2)
{
	int v3; // r8d
	__int64 v4; // r9
	__int64 result; // rax
	__int64 v6; // rdx

	v3 = 0;
	if (*(int*)(a1 + 0x2938) > 0)
	{
		v4 = 0i64;
		do
		{
			result = *(__int64*)(a1 + 10544);
			v6 = *(__int64*)(v4 + result);
			if (v6)
			{
				result = *(DWORD*)(v6 + 208) != 0;
				if ((DWORD)result == a2) {
					std::cout << std::hex << v6 + 168 << std::endl;
					*(__int64*)(v6 + 168) = 0i64;
				}
			}
			++v3;
			v4 += 8i64;
		} while (v3 < *(DWORD*)(a1 + 10552));
	}
	return result;
}

__int64 __fastcall ns4::attachobject::DisableSpecificAttachObject(__int64 a1, int a2)
{
	int v1; // r8d
	__int64 v3; // r9
	__int64 result; // rax
	DWORD* v5; // rcx
	v1 = 0;
	if (*(int*)(a1 + 10552) > 0)
	{
		v3 = 0i64;
		do
		{
			if (a2 == v1) {
				result = *(__int64*)(a1 + 10544);
				v5 = *(DWORD**)(v3 + result);
				std::cout << v5 << std::endl;
				if (v5)
				{
					v5[43] = 0;
					v5[42] = 0;
				}
			}
			++v1;
			v3 += 8i64;
		} while (v1 < *(DWORD*)(a1 + 10552));
	}
	return result;
}

__int64 __fastcall ns4::attachobject::EnableAttachObject(__int64 a1, int a2)
{
	int v2; // r8d
	__int64 v4; // r10
	__int64 result; // rax
	DWORD* v6; // rcx

	v2 = 0;
	if (*(int*)(a1 + 0x2938) > 0)
	{
		v4 = 0i64;
		do
		{
			result = *(__int64*)(a1 + 10544);
			v6 = *(DWORD**)(v4 + result);
			if (v6)
			{
				result = v6[52] != 0;
				if ((DWORD)result == a2)
				{
					v6[43] = 1;
					v6[42] = 1;
				}
			}
			++v2;
			v4 += 8i64;
		} while (v2 < *(DWORD*)(a1 + 0x2938));
	}
	return result;
}

__int64 __fastcall ns4::attachobject::EnableSpecificAttachObject(__int64 a1, int a2)
{
	int v2; // r8d
	__int64 v4; // r10
	__int64 result; // rax
	DWORD* v6; // rcx

	v2 = 0;
	if (*(int*)(a1 + 0x2938) > 0)
	{
		v4 = 0i64;
		do
		{
			if (a2 == v2) {
				result = *(__int64*)(a1 + 10544);
				v6 = *(DWORD**)(v4 + result);
				if (v6)
				{
					result = v6[52] != 0;
					v6[43] = 1;
					v6[42] = 1;
				}
			}
			++v2;
			v4 += 8i64;
		} while (v2 < *(DWORD*)(a1 + 0x2938));
	}
	return result;
}

__int64 __fastcall ns4::attachobject::ccPlayerCreate(__int64 a1, int a2, int r8d0, int a4, int a5, DWORD* a6) {
	auto retval = occPlayerCreate(a1, a2, r8d0, a4, a5, a6);
	//num++;
	std::string characode = (char*)ogetcharcode(*(DWORD*)(a1 + 0xC8C));
	std::string model = (char*)ogetcharcodemodel(*(DWORD*)(a1 + 0xC8C), *(DWORD*)(a1 + 0xC94));
	ns4::character c = ns4::character(characode);
	if (c.isvalid()) {
		test = 1;
		std::string asdf = (char*)ogetcharcodemodel(*(DWORD*)(a1 + 0xC8C), *(DWORD*)(a1 + 0xC94)) + *(char*)"trall";
		grdl.reinitreferencebone(asdf);
	}
	retval = occPlayerCreate(a1, a2, r8d0, a4, a5, a6);
	if (*(DWORD*)(a1 + 0xC8C) == 0x19)
		test = 0;
	return retval;
}
