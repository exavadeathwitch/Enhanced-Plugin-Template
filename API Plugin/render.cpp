#include <Windows.h>

#include "render.h"

#include "Main.h"

#include <iostream>

#include <vector>
__int64 blab = 0;
std::vector<__int64> testVector;

//Renders a frame of the game.
int __fastcall render::renderElements(__int64 a1, signed __int64 a2, unsigned int a3, int a4)
{
    int result; // eax@1
    int v5; // ebp@1
    __int64 v6; // rsi@3
    __int64 v7; // r15@6
    __int64** v8; // r14@6
    __int64* v9; // rdi@7
    __int64 v10; // rbx@7
    int v11; // edx@8
    __int64***** v12; // rdx@10
    __int64*** v13; // rcx@10
    __int64**** v14; // rdx@11
    unsigned __int64 v15; // r8@18
    __int64** v16; // rax@14
    __int64 v17; // rdx@16

    typedef __int64(__fastcall* sub_14053C910) (__int64 a1, int a2);
    sub_14053C910 osub_14053C910 = (sub_14053C910)(plugin::moduleBase + 0xAB8330 + 0xC00);

    result = 127;
    v5 = a4;
    if ((unsigned int)a2 >= 0x80)
        a2 = 127i64;
    v6 = a1;
    if (a3 >= 0x80)
        a3 = 127;
    if ((unsigned int)a2 <= a3)
    {
        result = a2;
        v7 = a3 - (unsigned int)a2 + 1;
        v8 = (__int64**)(a1 + 8 * ((unsigned int)a2 + 4 * a2 + 3));
        do
        {
            v9 = *v8;
            v10 = **v8;
            if ((__int64*)v10 != *v8)
            {
                do
                {
                    v11 = 0;
                    if (*(__int64*)(v6 + 5176) && v5)
                    {
                        v12 = *(__int64******)(v6 + 5144);
                        v13 = 0i64;
                        if (v12)
                        {
                            v14 = *v12;
                            if (v14)
                                v13 = *v14;
                        }
                        if (v13 && (v16 = *v13) != 0i64 && *v16)
                            v17 = **v16;
                        else
                            v17 = 0i64;
                        v15 = *(__int64*)(v6 + 0x1430) + *(__int64*)(v6 + 5176) - 1i64;
                        v11 = *(DWORD*)(*(__int64*)(*(__int64*)(v17 + 8) + 8 * ((*(__int64*)(v17 + 16) - 1i64) & (v15 >> 2)))
                            + 4 * (v15 & 3));
                    }
                    if (blab == 0)
                        blab = v10;
                    std::cout << std::hex << v10 << std::dec << std::endl;
                    uint8_t test = *(uint8_t*)(v10 + 224);
                    std::cout << (std::string)reinterpret_cast<const char*>((v10 + 224)) << std::endl;
                    if ((std::string)reinterpret_cast<const char*>((v10 + 224)) == "SceneRoot" && !render::hudon) {
                        NULL;
                    }
                    else
                        result = osub_14053C910(*(__int64*)(v10 + 16), v11);
                    v10 = *(__int64*)v10;
                } while ((__int64*)v10 != v9);
            }
            v8 += 5;
            --v7;
        } while (v7);
    }
    return result;
}

void __fastcall render::sub_14088E6A0(__int64 a1, __int64 a2, __int64 a3) {
    if (!render::hudon)
        return;
    return osub_14088E6A0(a1, a2, a3);
}

__int64 __fastcall render::sub_14089ADE0(__int64 a1, __int64 a2) {
    if (!render::hudon)
        return 0;
    return osub_14089ADE0(a1, a2);
}

__int64 __fastcall render::sub_1409DFC50(__int64* a1, __int64 a2) {
    return osub_1409DFC50(a1, a2);
    if (std::find(testVector.begin(), testVector.end(), a2) == testVector.end()) {
        testVector.push_back(a2);
    }
    std::cout << "size: " << int(testVector.size()) << std::endl;
    if (!render::hudon) {
        for (int i = 0; i < testVector.size(); i++) {
            if ((testVector[i] == a2) && ((i) == 0))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 1))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 2))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 3))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 4))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 5))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 6))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 7))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 8))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 9))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 10))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 11))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 12))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 13))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 14))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 15))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 16))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 17))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 18))
                return osub_1409DFC50(a1, a2);
            if ((testVector[i] == a2) && ((i) == 19))
                return osub_1409DFC50(a1, a2);
        }
        return 0;
    }
    return osub_1409DFC50(a1, a2);
}

__int64 __fastcall render::sub_1409E1EE0(__int64 a1, __int64 a2)
{
    return 0;
    /*
    __int64 v2; // rcx
    __int64 result; // rax
    __int64* v4; // rcx
    __int64 v5; // [rsp+20h] [rbp-18h]

    *(__int64*)&v5 = a1;
    *((__int64*)&v5 + 1) = a2;
    v2 = *(__int64*)(*(__int64*)(__readgsqword(0x58u) + 8i64 * (unsigned int)0x8A6A9CC) + 224i64);
    result = sub_1409DFC50(*(__int64*)v2, (unsigned __int64)*(unsigned int*)(v2 + 32) << 35);
    v4 = (__int64*)(result + 48);
    if (result == -48)
    {
        MEMORY[0x10] = 0i64;
    }
    else
    {
        *v4 = v5;
        *(__int64*)(result + 64) = v4;
    }
    return result;*/
}