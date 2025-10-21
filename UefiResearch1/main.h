#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/BaseMemoryLib.h> // for CopyMem
#include <Library/MemoryAllocationLib.h> // for AllocateZeroPool and FreePool

// smbios stuff
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Protocol/Smbios.h>
#include <intrin.h> // for __cpuid

// my files
#include <crypto/xor_str_export.h>
#include <utils/filesystem.h>
#include <utils/parser.h>

// #include "security.h"


#define MAX_STRING_LEN  200

extern UINTN gEfiSstringAAllocations;
extern UINTN gEfiSstringADestructions;

// patched when extracting
const UINT8 EncryptedData[192] = { 0 };
