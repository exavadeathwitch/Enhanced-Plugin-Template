#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

void MessageCommand();

__int64 Main::moduleBase = 0;
vector<__int64> Main::API_FunctionList;
// FunctionList:
// 00 Input::GetKey
// 01 Input::GetKeyDown
// 02 Input::GetKeyUp

// This function is called when booting the game.
void __stdcall InitializePlugin(__int64 a, std::vector<__int64> b)
{
	Main::moduleBase = a;
	Main::API_FunctionList = b;
}

// This function adds commands to the API's console.
void __stdcall InitializeCommands(__int64 a, __int64 addCommandFunctionAddress)
{
	typedef void(__stdcall *AddCmd)(std::string command, __int64 function, int paramcount);
	AddCmd AddCommand = (AddCmd)addCommandFunctionAddress;

	AddCommand("PluginTest", (__int64)MessageCommand, 0);
}

// Use this function to hook any of the game's original functions.
void __stdcall InitializeHooks(__int64 a, __int64 hookFunctionAddress)
{
	typedef void(__stdcall *HookFunct)(void* toHook, void* ourFunct, int len);
	HookFunct Hook = (HookFunct)hookFunctionAddress;
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
	cout << "Template by Zealot Tormunds" << endl;
}