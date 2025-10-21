#include <crypto/xor_str.hpp>

/* sha256.c */


/* main.c */
CREATE_XOR_STR16(StrGetWelcomeString, L"\r\nWelcome to research project\r\n\r\n");
CREATE_XOR_STR16(StrOriginalSystem, L"original System UUID: %g\r\n");
CREATE_XOR_STR16(StrOriginalBasebo, L"original baseboard serial: %a\r\n");
CREATE_XOR_STR16(StrOriginalSystem_0, L"original system serial: %a\r\n");

CREATE_XOR_STR16(StrDashSeparator30LF, L"------------------------------\r\n");

CREATE_XOR_STR16(StrFailedDecryptData, L"failed to decrypt data\r\n");
CREATE_XOR_STR16(StrDecryptedData, L"decrypted data:\r\n");
CREATE_XOR_STR16(StrFormatDecData, L"%a\r\n");

CREATE_XOR_STR16(StrFailedGetUuid, L"[MAIN] failed to get uuid from buff\r\n");
CREATE_XOR_STR16(StrFailedGetBb, L"[MAIN] failed to get base board serial from buff\r\n");
CREATE_XOR_STR16(StrFailedGetSysSerial, L"[MAIN] failed to get system serial from buff\r\n");

CREATE_XOR_STR16(StrModifiedUuid, L"Modified UUID: %g\r\n");
CREATE_XOR_STR16(StrModifiedBb, L"Modified BaseBoardSerial: %a\r\n");
CREATE_XOR_STR16(StrModifiedSysSerial, L"Modified SystemSerial: %a\r\n");

CREATE_XOR_STR16(StrStringAllocations, L"string allocs: %llu\r\n");
CREATE_XOR_STR16(StrStringDestructions, L"string destructions: %llu\r\n");

CREATE_XOR_STR16(StrPressAnyKeyToContinue, L"Press an key to continue . . .");


/* parser.c */
CREATE_XOR_STR16(FieldKeyNotFound, L"[-] Field key not found: %a\r\n");
CREATE_XOR_STR16(ErrorStrSubA1, L"[ParserGetFieldValueA] error while calling StrSubA");


/* security.c */
CREATE_XOR_STR16(ErrorGetHwidFingerprint1, L"[GetHwidFingerprint] Error while calling GetSmbiosPointers\r\n");
CREATE_XOR_STR16(ErrorGetHwidFingerprint2, L"[GetHwidFingerprint] Error while calling GetCpuProcessorId\r\n");

CREATE_XOR_STR16(ErrorGetHwidHash1, L"[GetHwidFingerprint] error while generating fingerprint\r\n");

CREATE_XOR_STR16(ErrorDecryptData1, L"[DecryptData] failed to get hwid fingerprint\r\n");
CREATE_XOR_STR16(ErrorDecryptData2, L"[DecryptData] failed to get decryption key from hwid fingerprint\r\n");
CREATE_XOR_STR16(ErrorDecryptData3, L"[DecryptData] failed to find null terminator in encrypted data\r\n");
CREATE_XOR_STR16(ErrorDecryptData4, L"[DecryptData] failed to decrypt data: invalid hwid fingerprint\r\n");
CREATE_XOR_STR16(LogHwidFingerprint, L"[DecryptData] hwid fingerprint: ");
CREATE_XOR_STR16(FormatByte, L"%X");
CREATE_XOR_STR16(FormatLf, L"\r\n");
