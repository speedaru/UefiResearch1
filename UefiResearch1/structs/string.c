#include <structs/string.h>

UINTN gEfiSstringAAllocations = 0;
UINTN gEfiSstringADestructions = 0;

// constructor, destructor
EFI_STRINGA EfiStringACreateDefault() {
    EFI_STRINGA s;
    EfiStringAAlloc(&s, DEFAULT_ALLOCATION_SIZE);
    return s;
}
EFI_STRINGA EfiStringACreate(const UINTN size) {
    EFI_STRINGA s;
    EfiStringAAlloc(&s, size);
    return s;
}
EFI_STRINGA EfiStringACreateFrom(const CHAR8 *source) {
    EFI_STRINGA s;
    UINTN size = MAX(AsciiStrLen(source) + 1, DEFAULT_ALLOCATION_SIZE); // +1: null terminator
    EfiStringAAlloc(&s, size);

    if (s.buff) {
        AsciiStrCpyS(s.buff, s.size - 1, source); // -1 so we cant overwrite null terminator
    }

    return s;
}
void EfiStringADestroy(EFI_STRINGA *this) {
    // dont destroy if invalid
    if (!EfiStringAIsPValid(this)) return;

    FreePool(this->buff);

    LOG_DBG(L"[EFI_STRINGA] freed EFI_STRINGA of %llu bytes at 0x%p\r\n", this->size, this->buff);

    // prevent use after free
    this->buff = NULL;
    this->size = 0;

    gEfiSstringADestructions++;
}

// manage memory
void EfiStringAAlloc(EFI_STRINGA *this, UINTN size) {
    if (!size) { // no size specified so use default size
        size = DEFAULT_ALLOCATION_SIZE;
    }

    this->buff = (CHAR8*)AllocateZeroPool(size);
    this->size = size;

    LOG_DBG(L"[EFI_STRINGA] Allocated %llu bytes for EFI_STRINGA at 0x%p\r\n", size, this->buff);

    gEfiSstringAAllocations++;
}
void EfiStringARealloc(EFI_STRINGA *this, UINTN newSize) {
    if (!newSize && !EfiStringAIsPValid(this)) { // if current string invalid and no size specified
        newSize = DEFAULT_ALLOCATION_SIZE;
    }
    else if (!newSize && EfiStringAIsPValid(this)) { // no specified size but current str valid
        // set newsize to +50%
        newSize = this->size + (this->size / 2); // ! dont use floats
    }

    LOG_DBG(L"[EFI_STRINGA] resizing EFI_STRINGA from %llu to %llu\r\n", this->size, newSize);

    if (this->buff) {
        EfiStringADestroy(this);
    }
    EfiStringAAlloc(this, newSize);
}
void EfiStringAEnsureValid(EFI_STRINGA *this, const UINTN minBytes) {
    // only realloc if minBytes stricly bigger than current size
    // reallocate if unallocated EFI_STRINGA or too small
    if (!EfiStringAIsPValid(this) || minBytes > this->size) {
        LOG_DBG(L"[EFI_STRINGA] EFI_STRINGA0 at 0x%p was not valid, reallocating ...\r\n", this->buff);
        EfiStringARealloc(this, minBytes);
    }
}

// string operations
void EfiStringAReplaceEx(EFI_STRINGA *this, const CHAR8 *newStr, UINTN newStrLen) {
    LOG_DBG(L"[EFI_STRINGA] replacing EFI_STRINGA at 0x%p with new string\r\n", this->buff);

    // reallocate buff if too small for new string
    EfiStringAEnsureValid(this, newStrLen + 1); // +1: have space for string + null terminator

    // copy string and add null terminator
    CopyMem(this->buff, newStr, newStrLen);
    this->buff[newStrLen] = '\0'; // set null terminator right after new text
}
