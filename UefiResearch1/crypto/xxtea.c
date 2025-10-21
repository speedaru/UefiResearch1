/**********************************************************\
|                                                          |
| xxtea.c                                                  |
|                                                          |
| XXTEA encryption algorithm library for C.                |
|                                                          |
| Encryption Algorithm Authors:                            |
|      David J. Wheeler                                    |
|      Roger M. Needham                                    |
|                                                          |
| Code Authors: Chen fei <cf850118@163.com>                |
|               Ma Bingyao <mabingyao@gmail.com>           |
| LastModified: Feb 7, 2016                                |
|                                                          |
\**********************************************************/


#include "xxtea.h"

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#if defined(_MSC_VER) && _MSC_VER < 1600
typedef unsigned __int8 uint8_t;
typedef unsigned __int32 uint32_t;
#else
#if defined(__FreeBSD__) && __FreeBSD__ < 5
/* FreeBSD 4 doesn't have stdint.h file */
#include <inttypes.h>
#else
#include <stdint.h>
#endif
#endif

#include <sys/types.h> /* This will likely define BYTE_ORDER */

#ifndef BYTE_ORDER
#if (BSD >= 199103)
# include <machine/endian.h>
#else
#if defined(linux) || defined(__linux__)
# include <endian.h>
#else
#define LITTLE_ENDIAN   1234    /* least-significant byte first (vax, pc) */
#define BIG_ENDIAN  4321    /* most-significant byte first (IBM, net) */
#define PDP_ENDIAN  3412    /* LSB first in word, MSW first in long (pdp)*/

#if defined(__i386__) || defined(__x86_64__) || defined(__amd64__) || \
   defined(vax) || defined(ns32000) || defined(sun386) || \
   defined(MIPSEL) || defined(_MIPSEL) || defined(BIT_ZERO_ON_RIGHT) || \
   defined(__alpha__) || defined(__alpha)
#define BYTE_ORDER    LITTLE_ENDIAN
#endif

#if defined(sel) || defined(pyr) || defined(mc68000) || defined(sparc) || \
    defined(is68k) || defined(tahoe) || defined(ibm032) || defined(ibm370) || \
    defined(MIPSEB) || defined(_MIPSEB) || defined(_IBMR2) || defined(DGUX) ||\
    defined(apollo) || defined(__convex__) || defined(_CRAY) || \
    defined(__hppa) || defined(__hp9000) || \
    defined(__hp9000s300) || defined(__hp9000s700) || \
    defined (BIT_ZERO_ON_LEFT) || defined(m68k) || defined(__sparc)
#define BYTE_ORDER  BIG_ENDIAN
#endif
#endif /* linux */
#endif /* BSD */
#endif /* BYTE_ORDER */

#ifndef BYTE_ORDER
#ifdef __BYTE_ORDER
#if defined(__LITTLE_ENDIAN) && defined(__BIG_ENDIAN)
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#endif
#ifndef BIG_ENDIAN
#define BIG_ENDIAN __BIG_ENDIAN
#endif
#if (__BYTE_ORDER == __LITTLE_ENDIAN)
#define BYTE_ORDER LITTLE_ENDIAN
#else
#define BYTE_ORDER BIG_ENDIAN
#endif
#endif
#endif
#endif

#define MX (((z >> 5) ^ (y << 2)) + ((y >> 3) ^ (z << 4))) ^ ((sum ^ y) + (key[(p & 3) ^ e] ^ z))
#define DELTA 0x9e3779b9

#define FIXED_KEY \
    UINTN i;\
    UINT8 fixed_key[16];\
    CopyMem(fixed_key, key, 16);\
    for (i = 0; (i < 16) && (fixed_key[i] != 0); ++i);\
    for (++i; i < 16; ++i) fixed_key[i] = 0;


static UINT32 *xxtea_to_uint_array(const UINT8* data, UINTN len, int inc_len, UINTN* out_len) {
    UINT32 *out;
#if !(defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN))
    UINTN i;
#endif
    UINTN n;

    n = (((len & 3) == 0) ? (len >> 2) : ((len >> 2) + 1));

    if (inc_len) {
        // allocate arary for n + 1 objects of type UINT32 (4 bytes)
        out = (UINT32*)AllocateZeroPool((n + 1) * sizeof(UINT32));
        if (!out) return NULL;
        out[n] = (UINT32)len;
        *out_len = n + 1;
    }
    else {
        // allocate arary for n objects of type UINT32 (4 bytes)
        out = (UINT32 *)AllocateZeroPool(n * sizeof(UINT32));
        if (!out) return NULL;
        *out_len = n;
    }
#if defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN)
    CopyMem(out, data, len);
#else
    for (i = 0; i < len; ++i) {
        out[i >> 2] |= (UINT32)data[i] << ((i & 3) << 3);
    }
#endif

    return out;
}

static UINT8 *xxtea_to_ubyte_array(const UINT32 *data, UINTN len, int inc_len, UINTN *out_len) {
    UINT8 *out;
#if !(defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN))
    UINTN i;
#endif
    UINTN m, n;

    n = len << 2;

    if (inc_len) {
        m = data[len - 1];
        n -= 4;
        if ((m < n - 3) || (m > n)) return NULL;
        n = m;
    }

    out = (UINT8 *)AllocateZeroPool(n + 1);

#if defined(BYTE_ORDER) && (BYTE_ORDER == LITTLE_ENDIAN)
    CopyMem(out, data, n);
#else
    for (i = 0; i < n; ++i) {
        out[i] = (UINT8)(data[i >> 2] >> ((i & 3) << 3));
    }
#endif

    out[n] = '\0';
    *out_len = n;

    return out;
}

static UINT32 *xxtea_uint_encrypt(UINT32 *data, UINTN len, UINT32 *key) {
    UINT32 n = (UINT32)len - 1;
    UINT32 z = data[n], y, p, q = 6 + 52 / (n + 1), sum = 0, e;

    if (n < 1) return data;

    while (0 < q--) {
        sum += DELTA;
        e = sum >> 2 & 3;

        for (p = 0; p < n; p++) {
            y = data[p + 1];
            z = data[p] += MX;
        }

        y = data[0];
        z = data[n] += MX;
    }

    return data;
}

static UINT32 *xxtea_uint_decrypt(UINT32 *data, UINTN len, UINT32 *key) {
    UINT32 n = (UINT32)len - 1;
    UINT32 z, y = data[0], p, q = 6 + 52 / (n + 1), sum = q * DELTA, e;

    if (n < 1) return data;

    while (sum != 0) {
        e = sum >> 2 & 3;

        for (p = n; p > 0; p--) {
            z = data[p - 1];
            y = data[p] -= MX;
        }

        z = data[n];
        y = data[0] -= MX;
        sum -= DELTA;
    }

    return data;
}

static UINT8 *xxtea_ubyte_encrypt(const UINT8 *data, UINTN len, const UINT8 *key, UINTN *out_len) {
    UINT8 *out;
    UINT32 *data_array, *key_array;
    UINTN data_len, key_len;

    if (!len) return NULL;

    data_array = xxtea_to_uint_array(data, len, 1, &data_len);
    if (!data_array) return NULL;

    key_array = xxtea_to_uint_array(key, 16, 0, &key_len);
    if (!key_array) {
        FreePool(data_array);
        return NULL;
    }

    out = xxtea_to_ubyte_array(xxtea_uint_encrypt(data_array, data_len, key_array), data_len, 0, out_len);

    FreePool(data_array);
    FreePool(key_array);

    return out;
}

static UINT8 *xxtea_ubyte_decrypt(const UINT8 *data, UINTN len, const UINT8 *key, UINTN *out_len) {
    UINT8 *out;
    UINT32 *data_array, *key_array;
    UINTN data_len, key_len;

    if (!len) return NULL;

    data_array = xxtea_to_uint_array(data, len, 0, &data_len);
    if (!data_array) return NULL;

    key_array = xxtea_to_uint_array(key, 16, 0, &key_len);
    if (!key_array) {
        FreePool(data_array);
        return NULL;
    }

    out = xxtea_to_ubyte_array(xxtea_uint_decrypt(data_array, data_len, key_array), data_len, 1, out_len);

    FreePool(data_array);
    FreePool(key_array);

    return out;
}

// public functions
void* xxtea_encrypt(const VOID *data, UINTN len, const VOID *key, UINTN *out_len) {
    FIXED_KEY;
    return xxtea_ubyte_encrypt((const UINT8 *)data, len, fixed_key, out_len);
}

void* xxtea_decrypt(const VOID *data, UINTN len, const VOID *key, UINTN *out_len) {
    FIXED_KEY;
    return xxtea_ubyte_decrypt((const UINT8 *)data, len, fixed_key, out_len);
}