#include <iostream>

#include "hooks.h"

#include "Main.h"

#include "render.h"

#include "Thirdparty/MinHook.h"

//Use minhook to hook all functions here.
void plugin::hookall() {
	plugin::hookfunc(moduleBase + 0xABD720 + 0xC00, render::renderElements, NULL);
	//plugin::hookfunc(moduleBase + 0x88DAA0 + 0xC00, render::sub_14088E6A0, (LPVOID*)&osub_14088E6A0);
	//plugin::hookfunc(moduleBase + 0x89A1E0 + 0xC00, render::sub_14089ADE0, (LPVOID*)&osub_14089ADE0);
	plugin::hookfunc(moduleBase + 0x9DF050 + 0xC00, render::sub_1409DFC50, (LPVOID*)&osub_1409DFC50);
	//plugin::hookfunc(moduleBase + 0x9E12E0 + 0xC00, render::sub_1409E1EE0, NULL);
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