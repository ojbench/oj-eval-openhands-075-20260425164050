#pragma once
#include <cstddef>

inline std::size_t strlen(const char* s) {
    const char* p = s;
    while (*p) ++p;
    return static_cast<std::size_t>(p - s);
}

inline int strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) { ++a; ++b; }
    unsigned char ca = static_cast<unsigned char>(*a);
    unsigned char cb = static_cast<unsigned char>(*b);
    if (ca == cb) return 0;
    return ca < cb ? -1 : 1;
}

inline char* strcpy(char* dst, const char* src) {
    char* d = dst;
    while ((*d++ = *src++)) {}
    return dst;
}

inline char* strcat(char* dst, const char* src) {
    char* d = dst;
    while (*d) ++d;
    while ((*d++ = *src++)) {}
    return dst;
}
