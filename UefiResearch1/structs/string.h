#ifndef STRING_H
#define STRING_H

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h> // for CopyMem

#define PRINT_DEBUG 0
#define PRINT_ERROR 0

#define LOG_DBG
#if PRINT_DEBUG == 1
    // redefine macro properly without warning
    #undef LOG_DBG
    #define LOG_DBG Print
#endif

#define LOG_ERR
#if PRINT_ERROR == 1
    // redefine macro properly without warning
    #undef LOG_ERR
    #define LOG_ERR Print
#endif


/**
    @param size includes null terminator
**/
typedef struct {
    CHAR8 *buff;
    UINTN size;
} EFI_STRINGA;

UINTN gEfiSstringAAllocations;
UINTN gEfiSstringADestructions;

// constructor, destructor
#define EfiStringAIsValid(this) (BOOLEAN)((this).buff && (this).size)
#define EfiStringAIsPValid(this) EfiStringAIsValid(*this)
EFI_STRINGA EfiStringACreateDefault();
EFI_STRINGA EfiStringACreate(const UINTN size);
EFI_STRINGA EfiStringACreateFrom(const CHAR8 *source);
void EfiStringADestroy(EFI_STRINGA *this);


// manage memory
#define DEFAULT_ALLOCATION_SIZE 0x40
/** 
    allocate new buffer
    @param size if 0 then its set to DEFAULT_ALLOCATION_SIZE
**/
void EfiStringAAlloc(EFI_STRINGA *this, UINTN size);
/**
    delete existing buffer (if exists) and alloc new one
    @param size if 0 then its set to DEFAULT_ALLOCATION_SIZE
**/
void EfiStringARealloc(EFI_STRINGA *this, UINTN newSize);
#define EfiStringAResize(this, newSize) EfiStringARealloc(this, newSize) 

/**
    if invalid string then allocate
    @param minBytes inclusive
**/
void EfiStringAEnsureValid(EFI_STRINGA *this, const UINTN minBytes);


// string operations;
/* Remarks: will perform rellocation ONLY if buffer too small */
void EfiStringAReplaceEx(EFI_STRINGA *this, const CHAR8 *newStr, UINTN newStrLen);
#define EfiStringAReplace(this, newStr) EfiStringAReplaceEx(this, newStr, AsciiStrLen(newStr))
#define EfiStringALen(this) MIN(AsciiStrLen((this)->buff), (this)->size) // if no null terminator then return size
// #define EfiStringALen(this) ((this)->size - 1)

#endif // STRING_H
