#include "filesystem.h"

EFI_STATUS FPOpenFile(
    IN CHAR16 *FilePath,
    OUT EFI_FILE_PROTOCOL **File,
    IN UINT64 FileMode,
    IN UINT64 Attributes
)
{
    EFI_STATUS Status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SimpleFS;
    EFI_FILE_PROTOCOL *Root;
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

    // Get the loaded image protocol
    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (VOID **)&LoadedImage);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to get LoadedImage protocol\n");
        return Status;
    }

    // Get the filesystem from the device handle
    Status = gBS->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (VOID **)&SimpleFS);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to get SimpleFileSystem protocol\n");
        return Status;
    }

    // Open volume (root directory)
    Status = SimpleFS->OpenVolume(SimpleFS, &Root);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to open root volume\n");
        return Status;
    }

    // Open file
    Status = Root->Open(Root, File, FilePath, FileMode, Attributes);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to open file: %s\n", FilePath);
        return Status;
    }

    return EFI_SUCCESS;
}

EFI_STATUS GetFileSizeEx(
    IN EFI_FILE_PROTOCOL *File,
    IN UINTN *pInfoSize,
    OUT EFI_FILE_INFO **pFileInfo
)
{
    UINTN InfoSize = *pInfoSize;

    EFI_STATUS Status;

    // Print(L"allocating %llu bytes\r\n", InfoSize);

    *pFileInfo = AllocateZeroPool(InfoSize);
    EFI_FILE_INFO *FileInfo = *pFileInfo;
    if (FileInfo == NULL) {
        File->Close(File);
        return EFI_OUT_OF_RESOURCES;
    }

    // Print(L"allocated %llu bytes at -> 0x%p\r\n", InfoSize, FileInfo);

    // Print(L"getting info . . .\r\n");

    // Print(L"[GetFileSize] FileInfo pval: 0x%p\n", FileInfo);
    Status = File->GetInfo(File, &gEfiFileInfoGuid, pInfoSize, FileInfo);
    if (EFI_ERROR(Status)) {
        Print(L"Failed to get file info\n");
        FreePool(FileInfo);
        File->Close(File);
        return Status;
    }

    // Print(L"got info: filename: '%ls' size: '%llu' !\r\n", FileInfo->FileName, FileInfo->FileSize);

    return EFI_SUCCESS;
}
EFI_STATUS
GetFileSize(
    IN CHAR16 *FilePath,
    OUT UINT64 *size
)
{
    EFI_FILE_PROTOCOL *File = NULL;
    EFI_STATUS Status = FPOpenFile(FilePath, &File, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    UINTN InfoSize = sizeof(EFI_FILE_INFO) + 200;
    EFI_FILE_INFO *FileInfo = NULL;
    Status = GetFileSizeEx(File, &InfoSize, &FileInfo);
    if (EFI_ERROR(Status)) {
        goto cleanup;
    }

    *size = FileInfo->FileSize;

    cleanup:
    FreePool(FileInfo);
    return Status;
}

EFI_STATUS
ReadFileToBuffer(
    IN CHAR16 *FilePath,
    OUT VOID **Buffer,
    OUT UINTN *BufferSize
)
{
    // Print(L"opening file %ls . . .\r\n", FilePath);

    EFI_FILE_PROTOCOL *File = NULL;
    EFI_STATUS Status = FPOpenFile(FilePath, &File, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(Status)) {
        return Status;
    }
    // Print(L"opened file %ls (handle: 0x%p) !\r\n", FilePath, File);

    // Print(L"getting %ls size . . .\r\n", FilePath);

    UINTN InfoSize = sizeof(EFI_FILE_INFO) + 200;
    EFI_FILE_INFO *FileInfo = NULL;
    Status = GetFileSizeEx(File, &InfoSize, &FileInfo);
    if (EFI_ERROR(Status)) {
        goto cleanup;
    }

    // Print(L"[ReadFileToBuffer] FileInfo pval: 0x%p\n", FileInfo);
    // Print(L"got %ls size: %llu\r\n", FilePath, FileInfo->FileSize);

    // allocate buffer and stuff
    // *BufferSize = FileInfo->FileSize;
    // *Buffer = AllocateZeroPool(*BufferSize + 1);
    // if (*Buffer == NULL) {
    //     FreePool(FileInfo);
    //     File->Close(File);
    //     return EFI_OUT_OF_RESOURCES;
    // }

    // Read file content
    Status = File->Read(File, BufferSize, *Buffer);
    if (EFI_ERROR(Status)) {
        goto cleanup;
    }
    ((UINT8*)*Buffer)[*BufferSize] = 0; // add null terminator

    cleanup:
    File->Close(File);
    FreePool(FileInfo);
    return Status;
}