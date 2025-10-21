#include <Uefi.h>
// #include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/LoadedImage.h>

#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Library/FileHandleLib.h> // optional helper


EFI_STATUS
FPOpenFile(
    IN CHAR16 *FilePath,
    OUT EFI_FILE_PROTOCOL **File,
    IN UINT64 FileMode,
    IN UINT64 Attributes
);

/**
    @param pFileInfo ALLOC, NO DELETE
**/
EFI_STATUS
GetFileSizeEx(
    IN EFI_FILE_PROTOCOL *File,
    IN UINTN *pInfoSize,
    OUT EFI_FILE_INFO **pFileInfo
);
EFI_STATUS
GetFileSize(
    IN CHAR16 *FilePath,
    OUT UINT64 *size
);

/**
    @param Buffer NO ALLOC, NO DELETE (must be preallocated and big enough)
**/
EFI_STATUS
ReadFileToBuffer(
    IN CHAR16 *FilePath,
    OUT VOID **Buffer,
    OUT UINTN *BufferSize
);