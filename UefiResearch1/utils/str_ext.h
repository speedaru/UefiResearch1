#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h> // for CopyMem

#include <structs/string.h>

/**
    @param StrBuff NO ALLOC, NO DELETE
**/
EFI_STATUS
StrFindA(
    // IN CHAR8 *StrBuff,
    // IN UINTN StrBuffSize,
    IN const EFI_STRINGA *String,
    IN const CHAR8 *Pattern,
    OUT UINTN *PatternStart,
    IN const UINTN SearchStartIndex,
    IN const UINTN SearchEndIndex
);

/**
    @param Result ALLOC, NO DELETE
    @param String the original from where to extract a substring

    @param SubStart start index of substring (inclusive)
    @param SubEnd index of where to end substring (exclusive)
**/
EFI_STATUS
StrSubA(
    // OUT CHAR8 *OutBuff,
    // IN UINTN OutBuffSize,
    OUT EFI_STRINGA *Result,
    IN const CHAR8 *String,
    IN const UINTN SubStart,
    IN const UINTN SubEnd
);

// EFI_STATUS
// StrConcatA(
//     OUT CHAR8 *OutBuff,
//     IN UINTN OutBuffSize,
//     IN CHAR8 *Str1,
//     IN UINTN Str1Len,
//     IN CHAR8 *Str2,
//     IN UINTN Str2Len,
//     IN BOOLEAN AddNullTerminator
// );