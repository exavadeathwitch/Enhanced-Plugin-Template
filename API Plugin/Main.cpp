#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "render.h"
#include "hooks.h"
#include "mem.hpp"

void MessageCommand();

//Variables that correspond to bytes nopped when no hud is enabled.
uint8_t jump;
uint8_t jump1;
uint8_t jump2;
uint8_t jump3;

// This function is called when booting the game. In the modding api, 0xC00 is added to the module base by default. In my modified code, I am removing it.
void __stdcall InitializePlugin(__int64 a, std::vector<__int64> b)
{
	plugin::moduleBase = a - 0xC00;
}

// This function adds commands to the API's console.
void __stdcall InitializeCommands(__int64 a, __int64 addCommandFunctionAddress)
{
	typedef void(__stdcall *AddCmd)(std::string command, __int64 function, int paramcount);
	AddCmd AddCommand = (AddCmd)addCommandFunctionAddress;

	//AddCommand("PluginTest", (__int64)MessageCommand, 0);
}

// Use this function to hook any of the game's original functions. I have modified this to initialize and then use minhook for hooks.
void __stdcall InitializeHooks(__int64 a, __int64 hookFunctionAddress)
{
	plugin::init();
	plugin::hookall();
	plugin::enableall();

	//Initializes original bytes that are overwritten when no hud is enabled.
	jump = *(uint8_t*)(plugin::moduleBase + 0x9A8EEE + 0xC00);
	jump1 = *(uint8_t*)(plugin::moduleBase + 0x9A8EEF + 0xC00);
	jump2 = *(uint8_t*)(plugin::moduleBase + 0x9A8EF0 + 0xC00);
	jump3 = *(uint8_t*)(plugin::moduleBase + 0x9A8EF1 + 0xC00);
}

// Use this function to add any lua commands to the game.
void __stdcall InitializeLuaCommands(__int64 a, __int64 addCommandFunction)
{
	typedef void(__stdcall *LuaAddFc)(std::string command, __int64 function);
	LuaAddFc LuaAddFunct = (LuaAddFc)addCommandFunction;

	// Example: This line adds a command "LuaTest", which calls the function LuaTest in this code.
	// LuaAddFunct("LuaTest", (__int64)LuaTest);
}

// This function will be called all the time while you're playing after the plugin has been initialized.
void __stdcall GameLoop(__int64 a)
{
	//This if statement enables and disables the hud.
	if ((GetAsyncKeyState(VK_ESCAPE) & 0x01)) {
		if (render::hudon) {
			std::cout << "No hud enabled!" << std::endl;
			render::hudon = 0;
			util::memory::mem::write_bytes<5>(plugin::moduleBase + 0x9A8EED + 0xC00, { 0x90, 0x90, 0x90, 0x90, 0x90 });
			plugin::disablehook(plugin::moduleBase + 0x9A8E9C + 0xC00);
		}
		else {
			std::cout << "No hud disabled!" << std::endl;
			render::hudon = 1;
			plugin::enablehook(plugin::moduleBase + 0x9A8E9C + 0xC00);
			util::memory::mem::write_bytes<1>(plugin::moduleBase + 0x9A8EED + 0xC00, { 0xE8 });
			util::memory::mem::write_bytes<1>(plugin::moduleBase + 0x9A8EEE + 0xC00, { jump });
			util::memory::mem::write_bytes<1>(plugin::moduleBase + 0x9A8EEF + 0xC00, { jump1 });
			util::memory::mem::write_bytes<1>(plugin::moduleBase + 0x9A8EF0 + 0xC00, { jump2 });
			util::memory::mem::write_bytes<1>(plugin::moduleBase + 0x9A8EF1 + 0xC00, { jump3 });
		}
	}
}

// This function is called when the API is loading a mod's files. Return true if the file was read by this plugin, otherwise return false for the API to manage the file.
bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes)
{
	return false;
}

void MessageCommand()
{
	std::cout << "No Hud Plugin" << std::endl;
}