#ifndef NSU_PTU_MY_SYMBOLS_H
#define NSU_PTU_MY_SYMBOLS_H

#include "my_bitset.c"
#include "my_tree.c"
#include <stdio.h>

typedef struct codes_for_symbols {
    char **codes;
    int *codes_lengths;
} codes_for_symbols;

static char output_file_extension[] = ".GOOOOOOL"; // 9 symbols

extern codes_for_symbols *coded_symbols;

void symbols_coding(TreeNode *current_node, char *current_code, int current_code_index, int current_code_capacity);

void symbols_decoding(FILE *input_file);

#endif
