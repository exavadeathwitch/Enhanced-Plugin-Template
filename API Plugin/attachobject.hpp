#pragma once

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include "Main.h"
#include "Thirdparty/nlohmann/json.hpp"

using json = nlohmann::json;
typedef __int64(__fastcall* ccUiGetMessage) (__int64 MessageToDecode);
inline ccUiGetMessage occUiGetMessage;

typedef int(__fastcall* sub_140654FD8) (__int64 a1, int* a2, const char* a3, int a4);
inline sub_140654FD8 osub_140654FD8;

typedef __int64(__fastcall* sub_140654848) (__int64 a1);
inline sub_140654848 osub_140654848;

typedef __int64(__fastcall* ccGetCharCode) (__int64 a1, int a2);
inline ccGetCharCode occGetCharCode;

typedef __int64*(__fastcall* sstrcpy) (void* Dst, char* Src, size_t Size);
inline sstrcpy ostrcpy;

typedef __int64(__fastcall* ccReplaceStringTag) (__int64* Src, char* a2, char* a3);
inline ccReplaceStringTag occReplaceStringTag;

namespace ns4 {
	class attachobj {
	public:
		__int64 characodeaddr;
		__int64 linkeraddr;
		__int64 referenceboneaddr;
		__int64 objpathaddr;//*(__int64*)((__int64)&objpath);
		__int64 objtypeaddr = 0; //0 for mesh, 1 for anim
		__int64 objnameaddr;
		__int64 objname2addr; //Optional
		float xpos;
		float ypos;
		float zpos;
		float xrot;
		float yrot;
		float zrot;
		float xscale;
		float yscale;
		float zscale;
		DWORD blank;
		DWORD appearancecond = 16;
		attachobj() {

		}
		attachobj(std::string characode, std::string referencebone, std::string objpath, DWORD objtype, std::string objname, std::string objname2) {
			this->characode = characode;
			this->referencebone = referencebone;
			this->objpath = objpath;
			this->objname = objname;
			this->objname2 = objname2;
			this->characodeaddr = (__int64)&this->characode;
			this->linkeraddr = (__int64)&this->characode;
			this->referenceboneaddr = (__int64)&this->referencebone;
			if (this->referencebone.size() >= 16)
				this->referencebone = *(__int64*)(this->referenceboneaddr);//*(__int64*)((__int64)&objpath);
			this->objpathaddr = (__int64)&this->objpath;//*(__int64*)((__int64)&objpath);
			if (this->objpath.size() >= 16)
				this->objpathaddr = *(__int64*)(this->objpathaddr);//*(__int64*)((__int64)&objpath);
			this->objtypeaddr = objtype; //0 for mesh, 1 for anim
			this->objnameaddr = (__int64)&this->objname;
			if (this->objname.size() >= 16)
				this->objnameaddr = *(__int64*)(this->objnameaddr);//*(__int64*)((__int64)&objpath);
			this->objname2addr = (__int64)&this->objname2; //Optional
			if (this->objname2.size() >= 16)
				this->objname2addr = *(__int64*)(this->objname2addr);//*(__int64*)((__int64)&objpath);
		}
		std::string getobjname() {
			return this->objname;
		}
		std::string getreferencebone() {
			return this->referencebone;
		}
		void initcoords(float xpos, float ypos, float zpos, float xrot, float yrot, float zrot, float xscale, float yscale, float zscale) {
			this->xpos = xpos;
			this->ypos = ypos;
			this->zpos = zpos;
			this->xrot = xrot;
			this->yrot = yrot;
			this->zrot = zrot;
			this->xscale = xscale;
			this->yscale = yscale;
			this->zscale = zscale;
		}
		void reinitreferencebone(std::string referencebone) {
			this->referencebone = referencebone;
			if (this->referencebone.size() >= 16)
				this->referenceboneaddr = *(__int64*)(this->referenceboneaddr);
		}
		void reinitobjpath(std::string objpath) {
			this->objpath = objpath;
			this->objpathaddr = (__int64)&this->objpath;
			if (this->objpath.size() >= 16)
				this->objpathaddr = *(__int64*)(this->objpathaddr);
		}
		void reinitobjname(std::string objname) {
			this->objname = objname;
			this->objnameaddr = (__int64)&this->objname;
			if (this->objname.size() >= 16)
				this->objnameaddr = *(__int64*)(this->objnameaddr);
		}
		void reinitobjname2(std::string objname2) {
			this->objname2 = objname2;
			this->objname2addr = (__int64)&this->objname;
			if (this->objname2.size() >= 16)
				this->objname2addr = *(__int64*)(this->objname2addr);
		}
		void reinit(std::string characode, std::string referencebone, std::string objpath, DWORD objtype, std::string objname, std::string objname2) {
			this->characode = characode;
			this->referencebone = referencebone;
			this->objpath = objpath;
			this->objname = objname;
			this->objname2 = objname2;
			this->characodeaddr = (__int64)&this->characode;
			this->linkeraddr = (__int64)&this->characode;
			this->referenceboneaddr = (__int64)&this->referencebone;
			if (this->referencebone.size() >= 16)
				this->referenceboneaddr = *(__int64*)(this->referenceboneaddr);//*(__int64*)((__int64)&objpath);
			this->objpathaddr = (__int64)&this->objpath;//*(__int64*)((__int64)&objpath);
			if (this->objpath.size() >= 16)
				this->objpathaddr = *(__int64*)(this->objpathaddr);//*(__int64*)((__int64)&objpath);
			this->objtypeaddr = objtype; //0 for mesh, 1 for anim
			this->objnameaddr = (__int64)&this->objname;
			if (this->objname.size() >= 16)
				this->objnameaddr = *(__int64*)(this->objnameaddr);//*(__int64*)((__int64)&objpath);
			this->objname2addr = (__int64)&this->objname2; //Optional
			if (this->objname2.size() >= 16)
				this->objname2addr = *(__int64*)(this->objname2addr);//*(__int64*)((__int64)&objpath);
		}
	private:
		std::string characode; //modelname?
		std::string referencebone;
		std::string objpath;
		std::string objname;
		std::string objname2 = "";
	};
	class character {
	public:
		std::string charcode;
		std::string costume;
		std::string path;
		attachobj guard = attachobj();
		character() {
		};
		character(std::string charcode) {
			this->charcode = charcode;
			this->path = ".\\character\\" + charcode + "\\guard\\";
		}
		bool isvalid() {
			//if base.json exists
			return true;
		}
		void readguardfile() {
			std::ifstream f(this->path + "\\base.json");
			json data = json::parse(f);
			guard = attachobj(charcode, data["referencebone"], data["objectpath"], data["objecttype"], data["objectname"], "");
		}
	};
	class attachobject {
	public:
		static __int64 __fastcall ccPlayerCreate(__int64 a1, int a2, int r8d0, int a4, int a5, DWORD* a6);
		static __int64 __fastcall GetPlayerAttachParamNum(__int64 a1, const char* a2, __int64 a3);
		static __int64 __fastcall CreateAttachObject(__int64 a1, __int64 nuccXfbinDocument, const char* bod1, const char* characode);
		static __int64 __fastcall EnableAttachObject(__int64 a1, int a2);
		static __int64 __fastcall EnableSpecificAttachObject(__int64 a1, int a2);
		static __int64 __fastcall DisableAttachObject(__int64 a1, int a2);
		static __int64 __fastcall DisableSpecificAttachObject(__int64 a1, int a2);
		static __int64 __fastcall GetPlayerAttachParam(__int64 a1, int a2, const char* a3, const char* a4);
	};
}