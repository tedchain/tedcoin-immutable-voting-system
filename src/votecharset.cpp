#include <iostream>
#include <algorithm>

#include "votecharset.h"
#include "uint256.h"
#include "script.h"

static const std::string strCharCodes = "0123456789abdefghijklmnopqrstuvwxyz ,.?!";

//first 8 bits - uint8_t with character count
bool ConvertTo6bit(std::string strFromUser, std::vector<unsigned char>& vchRet)
{
    std::transform(strFromUser.begin(), strFromUser.end(), strFromUser.begin(), ::tolower);
    uint160 v = 0;
    for (unsigned int i = 0; i < strFromUser.size(); i++) {
        char c = strFromUser[i];
        std::cout << "first in: " << c << std::endl;
        uint160 pos = strCharCodes.find(c);
        if (pos != std::string::npos) {
            v >>= 6;
            v |= pos << 154;
        }
        else
            return false;
    }

    v >>= 8;
    uint160 nSize = strFromUser.size();
    nSize <<= 152;
    v |= nSize;

    vchRet = ToByteVector(v);
    return true;
}

bool ConvertTo8bit(std::vector<unsigned char> vch, std::string& strRet)
{
    uint160 n = 0;
    for (unsigned int i = 0; i < vch.size(); i++) {
        n >>= 8;
        n |= uint160(vch[i]) << 154;
    }

    uint160 mask = 0x3f;
    mask <<= 154;
    uint160 nSize = n >> 152;
    std::cout << "size: " << nSize.Get64() << std::endl;
    for (int i = 0; i < nSize; i++) {
        uint160 j = n & mask;
        n >>= 6;
        std::cout << "j: " << j.Get64() << std::endl;
        char c = strCharCodes.at(j.Get64());
        std::cout << "letter: " << c << std::endl;
        strRet += c;
    }

    return true;
}
