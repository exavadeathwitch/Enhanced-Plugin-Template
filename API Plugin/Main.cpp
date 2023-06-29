#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "hooks.h"
#include "cpk.h"

void c_ConvertMessage();
void c_ViewMessageConversions();


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

// This function is called when the API is loading a mod's files. Return true if the file was read by this plugin, otherwise return false for the API to manage the file.
bool __stdcall ParseApiFiles(__int64 a, std::string filePath, std::vector<char> fileBytes)
{
	std::string _ext = filePath.substr(filePath.length() - 4, 4);
	if (_ext == ".cpk") {
		std::string cpkinfo = std::filesystem::path(filePath).replace_extension("cpk.info").string();
		std::string _file = filePath;
		if (std::filesystem::exists(cpkinfo))
		{
			std::vector<BYTE> fileBytes1 = ReadAllBytes(cpkinfo);
			int priority = fileBytes1[0] + (fileBytes1[1] * 0x100) + (fileBytes1[2] * 0x10000) + (fileBytes1[3] * 0x1000000);
			std::cout << "CpkLoader :: Priority set for cpk " << std::filesystem::path(_file).filename() << " to " << std::dec << priority << "." << std::endl;
			CpkToLoad.push_back(filePath);
			CpkPriority.push_back(priority);
		}
		else
		{
			std::cout << "CpkLoader :: Info file for cpk " << std::filesystem::path(_file).filename() << " was not found. Setting priority to default (13)." << std::endl;
			CpkToLoad.push_back(filePath);
			CpkPriority.push_back(13);
		}
		return true;
	}
	return false;
}
