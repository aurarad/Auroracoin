// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uint256.h"
/*#include "serialize.h"*/
#include "sph_luffa.h"
#include "sph_cubehash.h"
#include "sph_shavite.h"
#include "sph_simd.h"
#include "sph_echo.h"

/*#include <openssl/sha.h>
#include <openssl/ripemd.h>*/
#include <vector>


void qubit(const char *input, char *output)
{
    sph_luffa512_context     ctx_luffa;
    sph_cubehash512_context  ctx_cubehash;
    sph_shavite512_context   ctx_shavite;
    sph_simd512_context      ctx_simd;
    sph_echo512_context      ctx_echo;

    /*static unsigned char pblank[1];*/

    uint512 hash[4];

    sph_luffa512_init(&ctx_luffa);
    sph_luffa512(&ctx_luffa, input, 80);
    sph_luffa512_close(&ctx_luffa, static_cast<void*>(&hash[0]));

    sph_cubehash512_init(&ctx_cubehash);
    sph_cubehash512 (&ctx_cubehash, static_cast<const void*>(&hash[0]), 64);
    sph_cubehash512_close(&ctx_cubehash, static_cast<void*>(&hash[1]));

    sph_shavite512_init(&ctx_shavite);
    sph_shavite512(&ctx_shavite, static_cast<const void*>(&hash[1]), 64);
    sph_shavite512_close(&ctx_shavite, static_cast<void*>(&hash[2]));

    sph_simd512_init(&ctx_simd);
    sph_simd512 (&ctx_simd, static_cast<const void*>(&hash[2]), 64);
    sph_simd512_close(&ctx_simd, static_cast<void*>(&hash[3]));

    sph_echo512_init(&ctx_echo);
    sph_echo512 (&ctx_echo, static_cast<const void*>(&hash[3]), 64);
    /*sph_echo512_close(&ctx_echo, static_cast<void*>(&hash[4]));*/
    sph_echo512_close(&ctx_echo, (unsigned char*)&output);

    /*hash[4].trim256();

    output = (unsigned char*)&hash[4];*/
}
