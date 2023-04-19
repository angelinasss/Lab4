#include <cstddef>
#include <algorithm>
#include <bits/stdc++.h>

void* memcpy_(void* s1, const void* s2, size_t n) {
    if (s1 == NULL) return NULL;
    unsigned char* _s1 = (unsigned char*)s1;
    const unsigned char* _s2 = (const unsigned char*)s2;
    for (int i = 0; i < n; i++) {
        _s1[i] = _s2[i];
    }
    return s1;
}

void* memmove_(void* s1, const void* s2, size_t n) {
    void *res = s1;
    if (!(s1 <= s2 || (char*)s1 >= ((char*)s2 + n))) {
        s1 = (char*)s1 + n - 1;
        s2 = (char*)s2 + n - 1;
        for (size_t i = 0; i < n; i++) {
            *(char*)s1 = *(char*)s2;
            s1 = (char*)s1 - 1;
            s2 = (char*)s2 - 1;
        }
    }
    else {
        for (size_t i = 0; i < n; i++) {
        *(char*)s1 = *(char*)s2;
        s1 = (char*)s1 + 1;
        s2 = (char*)s2 + 1;
    }
    }
    return (res);
}

char* strcpy_(char* s1, const char* s2) {
    if (s1 == NULL)return NULL;
    char* return_ptr = s1;
    while (*s2 != '\0') {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return return_ptr;
}

char* strncpy_(char* s1, const char* s2, size_t n) {
    if (s1 == NULL || s2 == NULL || n == 0) return s1;
    size_t i = 0;
    while (i < n && s2[i] != '\0') {
        s1[i] = s2[i];
        i++;
    }
    while (i < n) {
        s1[i] = '\0';
        i++;
    }
    return s1;
}

size_t strlen_(const char* s) {
    if (*s == '\0') return 0;
    else return 1 + strlen_(s + 1);
}

char* strcat_(char* s1, const char* s2) {
    size_t i = strlen_(s1), j = 0;
    while (s2[j] != '\0') {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return s1;
}

char* strncat_(char* s1, const char* s2, size_t n) {
    size_t i = strlen_(s1), j = 0;
    while (s2[j] != '\0' && j != n) {
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return s1;
}

int memcmp_(const void* s1, const void* s2, size_t n) {
    int cmp = 0;
    const unsigned char* lhs = (unsigned char*)s1;
    const unsigned char* rhs = (unsigned char*)s2;

    for (size_t i = 0; i < n; i++) {
        if (lhs[i] == rhs[i]) {
            continue;
        }
        else if (lhs[i] < rhs[i]) {
            return -1;
        }
        else if (lhs[i] > rhs[i]) {
            return 1;
        }
    }

    return cmp;
}

int strncmp_(const char* s1, const char* s2, size_t n) {
    for (int i = 0; i < n; i++) {
        if (s1[i] == '\0' && s2[i] == '\0') return 0;
        if (s1[i] == s2[i]) {
            if (i == (n - 1)) return 0;
        }
        int a1 = (int)s1[i];
        int a2 = (int)s2[i];
        if (a1 > a2) return 1;
        if (a2 > a1) return -1;
    }
}

int strcmp_(const char* s1, const char* s2) {
    size_t max = std::max(strlen_(s1), strlen_(s2));
    return strncmp_(s1, s2, max);
}

char* strtok_(char* s1, char s2) {
    static char* index;

    if (s1 != NULL) {
        index = s1;
    }
    else {
        return NULL;
    }

    char* result = new char[strlen_(index) + 1];
    int i = 0;
    for (; index[i] != '\0'; i++) {
        if (index[i] != s2)
            result[i] = index[i];
        else {
            result[i] = '\0';
            index = index + i + 1;
            return result;
        }
    }
    result[i] = '\0';
    index = NULL;
    return result;
}

void* memset_(void* s, char c, size_t n) {
    int i = 0;
    unsigned char* p = (unsigned char*)s;
    for (int i = 0; i < n; i++) {
        *p = c;
        p++;
    }
    return s;
}

char* strerror_(int errnum) {
    switch (errnum) {
    case 0:
        return (char*)"No child processes";
    case 1:
        return (char*)"Operation not permitted";
    case 2:
        return (char*)"No such file or directory";
    case 3:
        return (char*)"No such process";
    case 4:
        return (char*)"Interrupted function call";
    case 5:
        return (char*)"Input/output error";
    case 6:
        return (char*)"No such device or address";
    case 7:
        return (char*)"Arg list too long";
    case 8:
        return (char*)"Exec format error";
    case 9:
        return (char*)"Bad file descriptor";
    case 10:
        return (char*)"Resource temporarily";
    case 11:
        return (char*)"unavailable";
    case 12:
        return (char*)"Not enough space";
    case 13:
        return (char*)"Permission denied";
    case 14:
        return (char*)"Bad address";
    case 15:
        return (char*)"Unknown error";
    case 16:
        return (char*)"No error";
    case 17:
        return (char*)"File exists";
    case 18:
        return (char*)"Improper link";
    case 19:
        return (char*)"No such device";
    case 20:
        return (char*)"Not a directory";
    case 21:
        return (char*)"Is a directory";
    case 22:
        return (char*)"File too large";
    case 23:
        return (char*)"Too many open files in system";
    case 24:
        return (char*)"Too many open files";
    case 25:
        return (char*)"Inappropriate I/O control operation";
    case 26:
        return (char*)"Unknown error";
    case 27:
        return (char*)"File too large";
    case 28:
        return (char*)"No space left on device";
    case 29:
        return (char*)"Invalid seek";
    case 30:
        return (char*)"Read-only file system";
    case 31:
        return (char*)"Too many links";
    case 32:
        return (char*)"Broken pipe";
    case 33:
        return (char*)"Domain error";
    case 34:
        return (char*)"Result too large";
    case 35:
        return (char*)"Unknown error";
    case 36:
        return (char*)"Resource deadlock avoided";
    case 37:
        return (char*)"Unknown error";
    case 38:
        return (char*)"Filename too long";
    default:
        return strerror(errnum);
    }
}
