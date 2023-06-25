#include "condition.h"

#include "Main.h"

#include <iostream>
#include <Windows.h>

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

void condition::ReadPartnerSlotParam(std::string _file)
{
	std::vector<BYTE> fileBytes = ReadAllBytes(_file);

	int slotCount = fileBytes.size() / 0x20;

	for (int x = 0; x < slotCount; x++)
	{
		std::string slotType = "";
		int slotCharacter = 0;
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

		//cout << "stuff: " << std::hex << (uintptr_t)fileBytes[actual] << " " << (uintptr_t)fileBytes[actual + 1] << endl;
		slotCharacter = (fileBytes[actual] * 0x1) + (fileBytes[actual + 1] * 0x100);

		int slotFunct = 0x0;

		if (slotType == "PARTNER_TYPE_2PAR") slotFunct = 0x2B; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2KKG") slotFunct = 0x2C; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2AKM") slotFunct = 0x29; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2KRS") slotFunct = 0x2A; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_1AKM") slotFunct = 0x66; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_1KRS") slotFunct = 0x6A; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_2SCX") slotFunct = 0x45; // UPDATED TO 12
		else if (slotType == "PARTNER_TYPE_8AEM") slotFunct = 0xE6; // UPDATED TO 12

		partnerfunction.push_back(slotFunct);
		partnercode.push_back(slotCharacter);

		//cout << "CharacterType = " << slotType.c_str() << ", Chara = " << std::hex << slotCharacter << endl;
	}
}

void condition::ReadSpecialConditionParam(std::string _file)
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

		int condFunct = 0x0;
		int actualConditionIndex = -1;
		bool found = false;

		if (slotType == "COND_1CMN") condFunct = 0x0;
		else if (slotType == "COND_2SIK") condFunct = 0xA;
		else if (slotType == "COND_2HDN") condFunct = 0x20;
		else if (slotType == "COND_2KKS") condFunct = 0x12;
		else if (slotType == "COND_2CYB") condFunct = 0x1B;
		else if (slotType == "COND_2SCO") condFunct = 0x1E;
		else if (slotType == "COND_2DDR") condFunct = 0x1F;
		else if (slotType == "COND_3HNZ") condFunct = 0x51;
		else if (slotType == "COND_3TOB") condFunct = 0x49;
		else if (slotType == "COND_3TYO") condFunct = 0x53;
		else if (slotType == "COND_3MDR_2") condFunct = 0x6F;
		else if (slotType == "COND_3KBT") condFunct = 0x5E;
		else if (slotType == "COND_2KNK") condFunct = 0x10;
		else if (slotType == "COND_2JRY") condFunct = 0x15;
		else if (slotType == "COND_3GAR") condFunct = 0x56; // same as below
		else if (slotType == "COND_2GAV") condFunct = 0x70; // same as above
		else if (slotType == "COND_2ORC") condFunct = 0x17;
		else if (slotType == "COND_5KGY") condFunct = 0x7C;
		else if (slotType == "COND_2FOU") condFunct = 0x2D;
		else if (slotType == "COND_2DNZ") condFunct = 0x3A;
		else if (slotType == "COND_3GUY") condFunct = 0xC4;
		else if (slotType == "COND_2KBT") condFunct = 0x18;
		else if (slotType == "COND_2MDR") condFunct = 0x39;
		else if (slotType == "COND_JKKS") condFunct = 0xB6;
		else if (slotType == "COND_2KIB") condFunct = 0x0C;
		else if (slotType == "COND_2KNN") condFunct = 0x26;
		else if (slotType == "COND_2SGT") condFunct = 0x22;
		else if (slotType == "COND_4MKG") condFunct = 0x57;
		else if (slotType == "COND_2NRT") condFunct = 0x01; // same as below
		else if (slotType == "COND_2NRG") condFunct = 0x37; // same as below
		else if (slotType == "COND_3NRT") condFunct = 0x54; // same as above
		else if (slotType == "COND_2NRX") condFunct = 0x02;
		else if (slotType == "COND_3SSK") condFunct = 0x55;
		else if (slotType == "COND_5TYY") condFunct = 0x76;
		else if (slotType == "COND_5MDR") condFunct = 0x72;
		else if (slotType == "COND_5KDM") condFunct = 0x74;
		else if (slotType == "COND_BMDR") condFunct = 0x78;
		else if (slotType == "COND_1KNK") condFunct = 0x69;
		else if (slotType == "COND_2YMT") condFunct = 0x1D;
		else if (slotType == "COND_3MDR") condFunct = 0x46;
		else if (slotType == "COND_5SKN") condFunct = 0x75;
		else if (slotType == "COND_5JRB") condFunct = 0x73;
		else if (slotType == "COND_7BRX") condFunct = 0xCE;
		else if (slotType == "COND_7SKD") condFunct = 0xD0;
		else if (slotType == "COND_7YRI") condFunct = 0xD3;
		else if (slotType == "COND_7NRN") condFunct = 0xC8;
		else if (slotType == "COND_7SSX") condFunct = 0xC9;
		else if (slotType == "COND_7MMS") condFunct = 0xD1;
		else if (slotType == "COND_7KIN") condFunct = 0xD2;
		else if (slotType == "COND_7GAR") condFunct = 0xCB;
		else if (slotType == "COND_7MTK") condFunct = 0xD8;
		else if (slotType == "COND_8MMS") condFunct = 0xDA;
		else if (slotType == "COND_8KIN") condFunct = 0xDB;
		else if (slotType == "COND_8KNK") condFunct = 0xE3;
		else if (slotType == "COND_8SIK") condFunct = 0xDD;
		else if (slotType == "COND_8TYO") condFunct = 0xDE;
		else if (slotType == "COND_BKRL") condFunct = 0x8C;
		else if (slotType == "COND_BSSN") condFunct = 0x8D;
		else if (slotType == "COND_BOBT") condFunct = 0x8E;
		else if (slotType == "COND_BKRS") condFunct = 0x9B;
		else if (slotType == "COND_B3HS") condFunct = 0xC5;
		else if (slotType == "COND_BGKT") condFunct = 0x8F;
		else if (slotType == "COND_BAOD") condFunct = 0x90;
		else if (slotType == "COND_BKTY") condFunct = 0x91;
		else if (slotType == "COND_1JBR") condFunct = 0x93;
		else if (slotType == "COND_2JBR") condFunct = 0x94;
		else if (slotType == "COND_3JBR") condFunct = 0x95;
		else if (slotType == "COND_4JBR") condFunct = 0x96;
		else if (slotType == "COND_5JBR") condFunct = 0x97;
		else if (slotType == "COND_6JBR") condFunct = 0x98;
		else if (slotType == "COND_GFSA") condFunct = 0x99;
		else if (slotType == "COND_BJYD") condFunct = 0x9A;
		else if (slotType == "COND_BKKX") condFunct = 0x8A;
		else if (slotType == "COND_B5OB") condFunct = 0x8B;
		else if (slotType == "COND_B4NR") condFunct = 0x89;
		else if (slotType == "COND_B2NR") condFunct = 0x92;
		else if (slotType == "COND_BJB1") condFunct = 0x85; // same as below
		else if (slotType == "COND_BJB2") condFunct = 0x86; // same as below
		else if (slotType == "COND_BJB3") condFunct = 0x87; // same as below
		else if (slotType == "COND_BJB4") condFunct = 0x88; // same as below
		else if (slotType == "COND_GFSA") condFunct = 0x99; // same as above
		else if (slotType == "COND_BGRG") condFunct = 0xA1;
		else if (slotType == "COND_GZTU") condFunct = 0xA2;
		else if (slotType == "COND_BRSK") condFunct = 0xA7;
		else if (slotType == "COND_BKMS") condFunct = 0xA8;
		else if (slotType == "COND_BKSR") condFunct = 0xA9;
		else if (slotType == "COND_BOBK") condFunct = 0xB7;
		else if (slotType == "COND_BNRX") condFunct = 0xB2;
		else if (slotType == "COND_BSSX") condFunct = 0xB3;
		else if (slotType == "COND_BISS") condFunct = 0xD5;
		else if (slotType == "COND_BMNK") condFunct = 0xD6;
		else if (slotType == "COND_7MMV") condFunct = 0xD7;

		charfunction.push_back(condFunct);
		charcodes.push_back(condCharacter);

	}
}

__int64 __fastcall condition::CreatePartner(__int64 player, int partnercharcode) {
	for (int x = 0; x < partnercode.size(); x++) {
		if (*(DWORD*)(player + 0xC8C) == partnercode.at(x))
		return gpio(player, partnerfunction.at(x));
	}
	return gpio(player, partnercharcode);
}

__int64 __fastcall condition::Create(int characterNum, int a2) {
	for (int x = 0; x < charcodes.size(); x++) {
		if (characterNum == charcodes.at(x))
			return co(charfunction.at(x), a2);
	}
	return co(characterNum, a2);
}