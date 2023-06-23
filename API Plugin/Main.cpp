#include "Main.h"
#include <stdio.h>
#include <vector>
#include <iostream>

#include "message.h"
#include "hooks.h"

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

	AddCommand("ConvertMessage", (__int64)c_ConvertMessage, 1);
	AddCommand("ViewMessageConversions", (__int64)c_ViewMessageConversions, 0);
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
	std::string _ext = filePath.substr(filePath.length() - 4, 4);
	if (_ext == "ns4s") {
		message::ReadMessageFile(filePath);
		return true;
	}
	return false;
}

void c_ConvertMessage()
{
	std::string param1;

	std::cout << "MSG >> ";
	std::cin >> param1;

	std::cout << reinterpret_cast<const char*>(g_MessageToString((__int64)&param1[0])) << std::endl;
}

void c_ViewMessageConversions()
{
	if (ViewMessageConversions == 0)
	{
		std::cout << "Enabling view of message conversions..." << std::endl;
		ViewMessageConversions = 1;
	}
	else
	{
		std::cout << "Disabling view of message conversions..." << std::endl;
		ViewMessageConversions = 0;
	}
}
