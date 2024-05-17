#ifndef NSU_PTU_HUFFMAN_COMPRESSING_H
#define NSU_PTU_HUFFMAN_COMPRESSING_H

#include "my_symbols.c"

void compression(FILE *input_file, char *input_file_name);

extern codes_for_symbols *coded_symbols;

#endif
