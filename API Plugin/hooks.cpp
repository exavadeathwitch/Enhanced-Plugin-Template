#include <iostream>

#include "hooks.h"

#include "Main.h"

#include "commandlist.hpp"

#include "Thirdparty/MinHook.h"

//Use minhook to hook all functions here.
void plugin::hookall() {
	plugin::hookfunc(moduleBase + 0x6543D8 + 0xC00, commandlist::functions::sub_140654FD8, (LPVOID*)&osub_140654FD8);
	plugin::hookfunc(moduleBase + 0x653C48 + 0xC00, commandlist::functions::sub_140654848, (LPVOID*)&osub_140654848);
	plugin::hookfunc(moduleBase + 0x7FE4C4 + 0xC00, commandlist::functions::ccGetCharCode, (LPVOID*)&occGetCharCode);
	plugin::hookfunc(moduleBase + 0x1CAB1C + 0xC00, commandlist::functions::strcpy, (LPVOID*)&ostrcpy);
	plugin::hookfunc(moduleBase + 0xAB8BB0 + 0xC00, commandlist::functions::ccReplaceStringTag, (LPVOID*)&occReplaceStringTag);
}

//Hooks a singular function.
bool plugin::hookfunc(__int64 funcaddr, LPVOID detourfunc, LPVOID* originalfunc = NULL) {
	bool status = MH_CreateHook((LPVOID)funcaddr, detourfunc, originalfunc);
	if (status != MH_OK)
	{
		if (enablemessages)
			std::cout << "Hook at " << funcaddr << " could not be created." << std::endl;
		return 0;
	}
	if (enablemessages)
		std::cout << "Hook at " << funcaddr << " was created." << std::endl;
	plugin::funclist.push_back(funcaddr);
	return 1;
}

//Initializes Minhook
bool plugin::init() {
	if (MH_Initialize() == MH_OK) {
		if (enablemessages)
			std::cout << "Minhook initialized" << std::endl;
		return 1;
	}
	if (enablemessages)
		std::cout << "Minhook not initialized" << std::endl;
	return 0;
}

//Enables a single hook.
bool plugin::enablehook(__int64 funcaddr) {
	bool status = MH_EnableHook((LPVOID)funcaddr);
	if (status != MH_OK)
	{
		if (enablemessages)
			std::cout << "Hook at " << funcaddr << " could not be enabled." << std::endl;
		return 0;
	}
	if (enablemessages)
		std::cout << "Hook at " << funcaddr << " was enabled." << std::endl;
	return 1;
}

//Disables a single hook.
bool plugin::disablehook(__int64 funcaddr) {
	bool status = MH_DisableHook((LPVOID)funcaddr);
	if (status != MH_OK)
	{
		if (enablemessages)
			std::cout << "Hook at " << funcaddr << " could not be disabled." << std::endl;
		return 0;
	}
	if (enablemessages)
		std::cout << "Hook at " << funcaddr << " was disabled." << std::endl;
	return 1;
}

//Enables every hook initialized in hookall.
void plugin::enableall() {
	for (__int64 i : plugin::funclist) {
		plugin::enablehook(i);
	}
}