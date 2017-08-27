#include <iostream>
#include <string>
#include "general.h"

#include <openssl/md5.h>

void calcAndPrintMD5(std::string& str)
{
    // kdyz uz jsme tak hezky nasli OpenSSL knihovnu, udelame alespon MD5 hash
    uint8_t digest[MD5_DIGEST_LENGTH];
    MD5((uint8_t*)str.c_str(), str.length(), digest);

    for (int i = 0; i < 16; i++)
        std::cout << std::hex << std::uppercase << (uint32_t)digest[i];
}

