#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "player.h"
#include "hooks.h"
#include "mem.hpp"

void MessageCommand();
void readsusanoocondparam(std::string _file);

std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::vector<BYTE> ReadAllBytes(std::string _file);
// This function is called when booting the game. In the modding api, 0xC00 is added to the module base by default. In my modified code, I am removing it.
void __stdcall InitializePlugin(__int64 a, std::vector<__int64> b)
{
	std::string f = GetExeFileName();
	std::string e = f.substr(0, f.length() - 10) + "moddingapi\\mods\\susanooJump\\";
	plugin::moduleBase = a - 0xC00;
	std::ifstream af(e + "susanooCondParam.xfbin");
	af.is_open();
	bool test = af.good();
	if (test) {
		readsusanoocondparam(e + "susanooCondParam.xfbin");
	}
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

// This function is called when the API is loading a mod's files. Return true if the file was read by this plugin, otherwise return false for the API to manage the file.
bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes)
{
	return false;
}

void MessageCommand()
{
	std::cout << "Susanoo Jump Fix" << std::endl;
}

std::vector<BYTE> ReadAllBytes(std::string _file)
{
	std::ifstream f;
	f.open(_file);

	int FileSize = 0;
	while (!f.eof())
	{
		f.get();
		FileSize++;
	}

	f.close();
	f.open(_file, std::ios::binary);

	//cout << _file.c_str() << endl;
	std::vector<BYTE> result(FileSize);

	f.seekg(0, std::ios::beg);

	for (int x = 0; x < FileSize; x++)
	{
		BYTE a = f.get();
		memcpy((void*)&result[0 + x], &a, 1);
	}

	f.close();

	return result;
}

void readsusanoocondparam(std::string _file)
{
	std::vector<BYTE> fileBytes = ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		std::string slotType = "";
		int condCharacter = 0;
		int actual = (0x20 * x);

		while (actual < (0x20 * x) + 0x17)
		{
			if (fileBytes[actual] != 0x0)
			{
				slotType = slotType + (char)fileBytes[actual];
				actual++;
			}
			else
			{
				actual = (0x20 * x) + 0x17;
			}
		}

		condCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);
		//cout << "stuff: " << std::hex << (uintptr_t)fileBytes[actual] << " " << (uintptr_t)fileBytes[actual + 1] << endl;
		
		int susanoochar = 0;
		if (slotType == "SSN_2ITC") susanoochar = 0x19;
		else if (slotType == "SSN_2SSZ") susanoochar = 0x38;
		else if (slotType == "SSN_3SSK") susanoochar = 0x55;
		else if (slotType == "SSN_4SSI") susanoochar = 0x60;
		
		ns4::susanoocharlist.push_back(susanoochar);
		ns4::charlist.push_back(condCharacter);

	}
}