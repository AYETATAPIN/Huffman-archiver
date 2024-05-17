#include "my_bitset.h"

void bitscpy(char *dst, char *src, int number_of_bits) {
    for (int i = 0; i < number_of_bits; ++i) {
        dst[i / 8] |= (src[i / 8] & (1 << (i % 8)));
    }
}

int bitscmp(char *str1, char *str2, int start, int len) {
    for (int i = 0; i < len; ++i) {
        if ((((str1[/*shift +*/ ((start + i) / 8)] >> ((start + i) % 8))) & 1) != (((str2[i / 8] >> (i % 8))) & 1))
            return 1;
    }
    return 0;
}