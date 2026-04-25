#pragma once
#include <stddef.h>

extern "C" {
size_t strlen(const char* s) {
    const char* p = s;
    while (*p) ++p;
    return (size_t)(p - s);
}

int strcmp(const char* a, const char* b) {
    while (*a && (*a == *b)) { ++a; ++b; }
    unsigned char ca = (unsigned char)(*a);
    unsigned char cb = (unsigned char)(*b);
    if (ca == cb) return 0;
    return ca < cb ? -1 : 1;
}

char* strcpy(char* dst, const char* src) {
    char* d = dst;
    while ((*d++ = *src++)) {}
    return dst;
}

char* strcat(char* dst, const char* src) {
    char* d = dst;
    while (*d) ++d;
    while ((*d++ = *src++)) {}
    return dst;
}
}
