#pragma once
extern "C" {
    #include <Uefi.h>
}

#define XOR_KEY 0x5D

#define CREATE_XOR_STR8(FuncName, Str)              \
extern "C" { \
    CHAR8 *FuncName(); \
} \
CHAR8 *FuncName() { \
    constexpr XorStr<CHAR8, sizeof(Str) / sizeof(CHAR8)> obf(Str); \
    return obf.decrypt(); \
} \

#define CREATE_XOR_STR16(FuncName, Str) \
extern "C" { \
    wchar_t *FuncName(); \
} \
wchar_t *FuncName() { \
    constexpr XorStr<wchar_t, sizeof(Str) / sizeof(wchar_t)> obf(Str); \
    return obf.decrypt(); \
} \


template<typename T, size_t N>
class XorStr {
public:
    T data[N];

    constexpr XorStr(const T (&str)[N], T key = static_cast<T>(0x55)) : data{} {
        for (size_t i = 0; i < N; ++i)
            data[i] = str[i] ^ key;
    }

    T* decrypt() const {
        static T result[N] = {};
        for (size_t i = 0; i < N; ++i)
            result[i] = data[i] ^ static_cast<T>(0x55);
        return result;
    }
};