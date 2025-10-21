#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <intrin.h> // for wchar_t

#include <crypto/xor_str_export.h>
#include "str_ext.h"


/**
    @param FileData NO ALLOC, NO DELETE
    @param Value ALLOC, NO DELETE
**/
EFI_STATUS
SpoofParserGetValueA(
    IN const EFI_STRINGA *FileData,
    IN const CHAR8 *FieldKey,
    OUT EFI_STRINGA *Value,
    IN const BOOLEAN AccountForEqualSign
);
