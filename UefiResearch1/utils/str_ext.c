#include "str_ext.h"

EFI_STATUS
StrFindA(
    IN const EFI_STRINGA *String,
    IN const CHAR8 *Pattern,
    OUT UINTN *PatternStart,
    IN const UINTN SearchStartIndex,
    IN const UINTN SearchEndIndex
)
{
    const UINTN PatternLen = AsciiStrLen(Pattern);
    // Print(L"pattern len: %llu\r\n", PatternLen);

    // set max index to seach for. IF its specified
    UINTN MaxIndex = EfiStringALen(String) - PatternLen;
    if (SearchEndIndex > 0) {
        MaxIndex = SearchEndIndex; // custom end index (not END OF STRING)
    }

    for (UINTN i = SearchStartIndex; i <= MaxIndex; i++) {
        BOOLEAN Found = TRUE;

        for (UINTN j = 0; j < PatternLen; j++) {
            if (String->buff[i + j] != Pattern[j]) {
                Found = FALSE;
                break;
            }
        }

        if (Found) {
            // Print(L"found pattern at index i: %llu\r\n", i);
            *PatternStart = i;
            return EFI_SUCCESS;
		}
    }

    *PatternStart = MaxIndex;
    return EFI_NOT_FOUND;
}

EFI_STATUS
StrSubA(
    OUT EFI_STRINGA *Result,
    IN const CHAR8 *String,
    IN const UINTN SubStart,
    IN const UINTN SubEnd
)
{
    UINTN SubStrLen = SubEnd - SubStart;
    EfiStringAReplaceEx(Result, String + SubStart, SubStrLen);
    // UINTN SubStrLen = SubEnd - SubStart;
    // if (SubStrLen + AddNullTerminator > Result->size) {
    //     Print(L"[StrSubA] substring size(%llu) is bigger than output buffer size(%llu)\r\n",
    //         SubStrLen + AddNullTerminator, OutBuffSize);
    //     return EFI_BUFFER_TOO_SMALL;
    // }

    // CopyMem(OutBuff, InBuff + StartIndex, SubStrLen);

    // if (AddNullTerminator) {
    //     OutBuff[SubStrLen] = (CHAR8)0;
    // }

    return EFI_SUCCESS;
}

// EFI_STATUS
// StrConcatA(
//     OUT CHAR8 *OutBuff,
//     IN UINTN OutBuffSize,
//     IN CHAR8 *Str1,
//     IN UINTN Str1Len,
//     IN CHAR8 *Str2,
//     IN UINTN Str2Len,
//     IN BOOLEAN AddNullTerminator
// )
// {
//     if (OutBuffSize <= 0) {
//         Print(L"out buff size is 0\r\n");
//         return EFI_BUFFER_TOO_SMALL;
//     }

//     if (OutBuffSize < Str1Len) {
//         Print(L"cant get substr bcs outbuff too small. \
//             outBuffSize: %llu, Str1Len: %llu\r\n", OutBuffSize, Str1Len);
//         return EFI_BUFFER_TOO_SMALL;
//     }

//     EFI_STATUS Status = AsciiStrCpyS(OutBuff, OutBuffSize, Str1);
//     if (EFI_ERROR(Status)) {
//         Print(L"[StrSubA] cant copy str1(0x%p) into oubuff (0x%p): 0x%llu\r\n", Str1, OutBuff, Status);
//         return Status;
//     }
    
//     // change outBuff start so that we can append str2
//     OutBuff += Str1Len;
//     OutBuffSize -= Str1Len;

//     if (OutBuffSize < Str2Len) {
//         Print(L"cant get substr bcs outbuff too small. \
//             new outBuffSize: %llu, Str2Len: %llu\r\n", OutBuffSize, Str2Len);
//         return EFI_BUFFER_TOO_SMALL;
//     }

//     Status = AsciiStrCpyS(OutBuff, OutBuffSize, Str2);
//         if (EFI_ERROR(Status)) {
//         Print(L"[StrSubA] cant copy str2(0x%p) into oubuff (0x%p): 0x%llu\r\n", Str2, OutBuff, Status);
//         return Status;
//     }

//     if (AddNullTerminator) {
//         OutBuff[OutBuffSize - 1] = (char)0;
//     }

//     return EFI_SUCCESS;
// }