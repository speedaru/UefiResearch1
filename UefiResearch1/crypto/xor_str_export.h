#include <Uefi.h>

#ifndef XOR_STR_EXPORT_H
#define XOR_STR_EXPORT_H

#define ADD_EXPORT8(FuncName)    CHAR8 *FuncName();
#define ADD_EXPORT16(FuncName)    CHAR16 *FuncName();

// #define PRINT_XOR_STR8(FuncName, BuffSize)  \
//     CHAR8 buffer_FuncName[BuffSize];        \
//     GetWelcomeString(buffer_FuncName);      \
//     AsciiPrint(buffer_FuncName);            \

// #define PRINT_XOR_STR16(FuncName, BuffSize) \
//     CHAR16 buffer_FuncName[BuffSize];       \
//     GetWelcomeString(buffer_FuncName);      \
//     Print(buffer_FuncName);                 \


#ifdef __cplusplus
    extern "C" {
#endif

    // main.c
    ADD_EXPORT16(StrGetWelcomeString);
    ADD_EXPORT16(StrOriginalSystem);
    ADD_EXPORT16(StrOriginalBasebo);
    ADD_EXPORT16(StrOriginalSystem_0);

    ADD_EXPORT16(StrDashSeparator30LF);

    ADD_EXPORT16(StrFailedDecryptData);
    ADD_EXPORT16(StrDecryptedData);
    ADD_EXPORT16(StrFormatDecData);

    ADD_EXPORT16(StrFailedGetUuid);
    ADD_EXPORT16(StrFailedGetBb);
    ADD_EXPORT16(StrFailedGetSysSerial);

    ADD_EXPORT16(StrModifiedUuid);
    ADD_EXPORT16(StrModifiedBb);
    ADD_EXPORT16(StrModifiedSysSerial);

    ADD_EXPORT16(StrStringAllocations);
    ADD_EXPORT16(StrStringDestructions);

    ADD_EXPORT16(StrPressAnyKeyToContinue);


    // parser.c
    ADD_EXPORT16(FieldKeyNotFound);
    ADD_EXPORT16(ErrorStrSubA1);


    // security.c
    ADD_EXPORT16(ErrorGetHwidFingerprint1);
    ADD_EXPORT16(ErrorGetHwidFingerprint2);

    ADD_EXPORT16(ErrorGetHwidHash1);

    ADD_EXPORT16(ErrorDecryptData1);
    ADD_EXPORT16(ErrorDecryptData2);
    ADD_EXPORT16(ErrorDecryptData3);
    ADD_EXPORT16(ErrorDecryptData4);
    ADD_EXPORT16(LogHwidFingerprint);
    ADD_EXPORT16(FormatByte);
    ADD_EXPORT16(FormatLf);
    

    // ----------------------------------------

#ifdef __cplusplus
    }
#endif

#endif // XOR_STR_EXPORT_H
