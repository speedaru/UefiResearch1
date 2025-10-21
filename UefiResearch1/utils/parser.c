#include "parser.h"

EFI_STATUS
SpoofParserGetValueA(
    IN const EFI_STRINGA *FileData,
    IN const CHAR8 *FieldKey,
    OUT EFI_STRINGA *Value,
    IN const BOOLEAN AccountForEqualSign
)
{
    UINTN KeyStartIndex = 0;
    UINTN LineEndIndex = 0;

    EFI_STATUS Status = StrFindA(FileData, FieldKey, &KeyStartIndex, 0, 0);
    if (EFI_ERROR(Status)) {
        LOG_ERR(FieldKeyNotFound(), FieldKey); // L"[-] Field key not found: %a\r\n"
        return Status;
    }

    UINTN FieldKeyLen = AsciiStrLen(FieldKey);
    if (AccountForEqualSign) { // if true then len + 1 to account for '='
        FieldKeyLen++;
    }

    // start searching for \r\n start from first char in value
    // LineEndIndex will be excluded automatically
    const CHAR8 *LINE_END = "\r\n";
    Status = StrFindA(FileData, LINE_END, &LineEndIndex, KeyStartIndex + FieldKeyLen, 0);
    if (Status == EFI_NOT_FOUND) {
        LineEndIndex = EfiStringALen(FileData);
    }

    // Print(L"Pattern '%a' indexes: (key start: %llu, value start: %llu, end: %llu)\r\n", FieldKey, KeyStartIndex, KeyStartIndex + FieldKeyLen, LineEndIndex);

    UINTN SubStrStartIndex = KeyStartIndex + FieldKeyLen;
    Status = StrSubA(Value, FileData->buff, SubStrStartIndex, LineEndIndex); // will realloc Value if too small
    if (EFI_ERROR(Status)) {
        LOG_ERR(ErrorStrSubA1()); // L"[ParserGetFieldValueA] error while calling StrSubA"
        goto cleanup;
    }

    // Print(L"[ParserGetFieldValueA] SUBSTRRR bytes:\r\n", Value->buff);
    // {
    //     for (int i = 0; i < Value->size; i++) {
    //         Print(L"%02X ", Value->buff[i]);
    //     }
    // }
    // Print(L"\r\n");

    cleanup:
    return Status;
}
