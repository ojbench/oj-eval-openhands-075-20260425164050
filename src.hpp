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
    if (dst == src) return dst;
    std::size_t n = my_strlen(src);
    const char* s = src;
    char* d = dst;
    if (d > s && d < s + n + 1) {
        for (std::size_t i = 0; i <= n; ++i) d[n - i] = s[n - i];
    } else {
        for (std::size_t i = 0; i <= n; ++i) d[i] = s[i];
    }
    return dst;
}

inline char* my_strcat(char* dst, const char* src) {
    if (!dst) return nullptr;
    if (!src) return dst; // nothing to append
    std::size_t dlen = my_strlen(dst);
    std::size_t slen = my_strlen(src);
    char* d = dst + dlen;
    const char* s = src;
    if (d > s && d < s + slen + 1) {
        // overlap: copy backwards including null terminator
        for (std::size_t i = 0; i <= slen; ++i) d[slen - i] = s[slen - i];
    } else {
        for (std::size_t i = 0; i <= slen; ++i) d[i] = s[i];
    }
    return dst;
}

#define strlen  my_strlen
#define strcmp  my_strcmp
#define strcpy  my_strcpy
#define strcat  my_strcat
