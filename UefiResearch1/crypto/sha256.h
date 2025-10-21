/*********************************************************************
* Filename:   sha256.h
* Author:     Brad Conte (brad AT bradconte.com)
* Copyright:
* Disclaimer: This code is presented "as is" without any guarantees.
* Details:    Defines the API for the corresponding SHA1 implementation.
*********************************************************************/
#pragma once
#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <Uefi.h>
#include <Library/BaseMemoryLib.h> // copy mem

#include <structs/string.h>
// #include <stddef.h>
// #include <cstdint>
// #include <Windows.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

/**************************** DATA TYPES ****************************/
#ifndef BYTE
	typedef UINT8 BYTE;             // 8-bit byte
#endif
#ifndef DWORD
	typedef UINT32 DWORD;             // 32-bit word, change to "long" for 16-bit machines
#endif

typedef struct {
	BYTE data[64];
	DWORD datalen;
	unsigned long long bitlen;
	DWORD state[8];
} SHA256_CTX;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA256_CTX* ctx);
void sha256_update(SHA256_CTX* ctx, const BYTE data[], UINTN len);
void sha256_final(SHA256_CTX* ctx, BYTE hash[]);

#endif   // SHA256_H