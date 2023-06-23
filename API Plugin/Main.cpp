#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "hooks.h"

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

}

void ReadPatchFile(std::string _file)
{
	int SlashCount = 0;
	int ExtensionAddress = 0;
	for (int x = 0; x < _file.length(); x++)
	{
		if (_file[x] == '\\') SlashCount++;
		if (_file[x] == '.') ExtensionAddress = x;
	}

	int StartAddress = 0;
	int SlashesPassed = 0;
	for (int x = 0; x < _file.length(); x++)
	{
		if (_file[x] == '\\') SlashesPassed++;

		if (SlashesPassed == SlashCount)
		{
			StartAddress = x + 1;
			x = _file.length();
		}
	}

	std::string Hex = _file.substr(StartAddress, ExtensionAddress - StartAddress);

	//cout << Hex << endl;

	uintptr_t Address = 0;

	try
	{
		Address = strtol(Hex.c_str(), NULL, 16);
	}
	catch (std::exception e)
	{
		Address = 0;
	}

	if (Address > 0x13B4DAC) Address = Address + 0x400;
	else if (Address > 0xEAAFAC) Address = Address + 0x400;

	//cout << std::hex << Address << endl;

	std::ifstream f;
	f.open(_file);

	std::vector<BYTE> replace;
	int count = 0;
	while (!f.eof())
	{
		replace.push_back(f.get());
		count++;
	}

	if (Address != 0x0)
	{
		DWORD dwOld = 0;
		VirtualProtect((void*)(plugin::moduleBase + Address + 0xC00), replace.size(), PAGE_EXECUTE_READWRITE, &dwOld);
		BYTE v[0x1000];
		for (int x = 0; x < count; x++)
		{
			v[x] = replace[x];
		}

		//cout << "Patch";
		std::cout << "Patched .exe at " << std::hex << Address << " (" << std::hex << plugin::moduleBase + Address + 0xC00 << ")" << std::endl;
		memcpy((void*)(plugin::moduleBase + Address + 0xC00), &v, count - 1);
		VirtualProtect((void*)(plugin::moduleBase + Address + 0xC00), replace.size(), dwOld, &dwOld);
	}

	f.close();
}

// This function is called when the API is loading a mod's files. Return true if the file was read by this plugin, otherwise return false for the API to manage the file.
bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes)
{
	std::string _ext = filePath.substr(filePath.length() - 4, 4);
	if (_ext == "ns4p") {
		ReadPatchFile(filePath);
		return true;
	}
	return false;
}