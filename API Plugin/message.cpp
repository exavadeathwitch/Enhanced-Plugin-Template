#include "message.h"

#include "Main.h"

std::vector<std::string> message::ReadMessageFile(std::string _file)
{
	
	std::ifstream f;
	f.open(_file);

	std::vector<std::string> Messages;
	std::string actual = "";
	while (!f.eof())
	{
		char a = f.get();

		if (a != 0x00)
		{
			actual = actual + a;
		}
		else
		{
			//cout << "Push back " << actual << endl;
			Messages.push_back(actual);
			actual = "";
		}
	}

	f.close();
	for (int x = 0; x + 1 < Messages.size(); x = x + 2) {
		MessageID.push_back(Messages[x]);
		MessageStr.push_back(Messages[x + 1]);
	}
	return Messages;
}

uintptr_t message::Hook_MsgToString(uintptr_t MessageToDecode)
{
	
	if (ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		const char* result = reinterpret_cast<const char*>(g_MessageToString(MessageToDecode));

		if (MessageToDecode != 0)
		{
			bool finished = false;

			std::string message((char*)MessageToDecode);

			if (finished == false)
			{
				std::string msg = (std::string)(char*)MessageToDecode;

				for (int x = 0; x < MessageID.size(); x++)
				{
					std::string test = MessageID[x];
					if (msg == test)
						result = (char*)MessageStr[x].c_str();
				}
				if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}
		}

		return (uintptr_t)result;
	}
	else
	{
		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}

uintptr_t message::Hook_MsgToString_Alt(uintptr_t MessageToDecode)
{
	
	if (ViewMessageConversions == 0 && strlen((char*)MessageToDecode) > 0 && *(char*)MessageToDecode != '+')
	{
		const char* result = reinterpret_cast<const char*>(g_MessageToString2(MessageToDecode));

		if (MessageToDecode != 0)
		{
			bool finished = false;

			std::string message((char*)MessageToDecode);

			
			std::string msg = (std::string)(char*)MessageToDecode;

			for (int x = 0; x < MessageID.size(); x++)
			{
				std::string test = MessageID[x];
				if (msg == test)
					result = (char*)MessageStr[x].c_str();
			}
			if (msg != (std::string)(char*)MessageToDecode) result = (char*)msg.c_str();
			}

		return (uintptr_t)result;
	}
	else
	{

		if (*(char*)MessageToDecode == '+')
		{
			return (MessageToDecode + 1);
		}

		return MessageToDecode;
	}
}
