#pragma once
#include <cstddef>

inline std::size_t my_strlen(const char* s) {
    if (!s) return 0;
    const char* p = s;
    while (*p) ++p;
    return static_cast<std::size_t>(p - s);
}

inline int my_strcmp(const char* a, const char* b) {
    unsigned char ca, cb;
    if (!a) a = "";
    if (!b) b = "";
    while (true) {
        ca = static_cast<unsigned char>(*a++);
        cb = static_cast<unsigned char>(*b++);
        if (ca != cb) return ca < cb ? -1 : 1;
        if (cb == 0) return 0;
    }
}

inline char* my_strcpy(char* dst, const char* src) {
    if (!dst) return nullptr;
    if (!src) { *dst = '\0'; return dst; }
    char* d = dst;
    while ((*d++ = *src++)) {}
    return dst;
}

inline char* my_strcat(char* dst, const char* src) {
    if (!dst) return nullptr;
    char* d = dst;
    while (*d) ++d;
    if (!src) { *d = '\0'; return dst; }
    while ((*d++ = *src++)) {}
    return dst;
}

#define strlen  my_strlen
#define strcmp  my_strcmp
#define strcpy  my_strcpy
#define strcat  my_strcat
