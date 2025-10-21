#include "main.h"




/**
    The user Entry Point for Application. The user code starts with this function
    as the real entry point for the application.

    @param[in] ImageHandle    The firmware allocated handle for the EFI image.
    @param[in] SystemTable    A pointer to the EFI System Table.

    @retval EFI_SUCCESS       The entry point is executed successfully.
    @retval other             Some error occurs when executing this entry point.
**/

EFI_STATUS
EFIAPI
UefiMain (
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
)
{
    Print(StrGetWelcomeString()); // L"Welcome to research project\r\n"

    // [...]

    LOG_DBG(StrStringAllocations(), gEfiSstringAAllocations); // L"string allocs: %llu\r\n"
    LOG_DBG(StrStringDestructions(), gEfiSstringADestructions); // L"string destructions: %llu\r\n"

    EFI_INPUT_KEY _Key;
    UINTN StringBufferSize = MAX_STRING_LEN * sizeof (CHAR16);
    CHAR16* StringBuffer1 = AllocateZeroPool(StringBufferSize);
    ASSERT (StringBuffer1 != NULL);
    StrCpyS(StringBuffer1, MAX_STRING_LEN, StrPressAnyKeyToContinue()); // L"Press an key to continue . . ."

    CreatePopUp(EFI_WHITE | EFI_BACKGROUND_CYAN, &_Key, StringBuffer1, NULL);

    FreePool(StringBuffer1);
    return EFI_SUCCESS;
}
