#include "uint256.h"
#include <openssl/sha.h>

void sha256d(const char *input, char *output)
{
    uint256 hash1;

    SHA256((unsigned char*)input, 80, (unsigned char*)&hash1);
    SHA256((unsigned char*)&hash1, sizeof(hash1), (unsigned char*)&output);
}
