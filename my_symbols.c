#include "my_symbols.h"

extern codes_for_symbols *coded_symbols;

void symbols_coding(TreeNode *current_node, char *current_code, int current_code_index, int current_code_capacity) {
    if (current_node->left != NULL) {
        current_code[current_code_index / 8] |= (1 << (current_code_index % 8));
        if (current_code_index / 8 + 1 > current_code_capacity) {
            current_code_capacity *= 2;
            current_code = realloc(current_code, sizeof(char) * current_code_capacity);
        }
        symbols_coding(current_node->left, current_code, current_code_index + 1, current_code_capacity);
    }
    if (current_node->right != NULL) {
        current_code[current_code_index / 8] &= (~(1 << (current_code_index % 8)));
        if (current_code_index / 8 > current_code_capacity) {
            current_code_capacity *= 2;
            current_code = realloc(current_code, sizeof(char) * current_code_capacity);
        }
        symbols_coding(current_node->right, current_code, current_code_index + 1, current_code_capacity);
    }
    if (current_node->is_symbol == 1 && coded_symbols->codes_lengths[current_node->symbol] == 0) {
        coded_symbols->codes[current_node->symbol] = calloc(current_code_index, sizeof(char) * (current_code_index / 8 + 1));
        bitscpy(coded_symbols->codes[current_node->symbol], current_code, current_code_index);
        coded_symbols->codes_lengths[current_node->symbol] = current_code_index + 1;
    }
}

void symbols_decoding(FILE *input_file) {
    unsigned char current_symbol;
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        unsigned char decoding_symbol = current_symbol;
        fread(&coded_symbols->codes_lengths[decoding_symbol], sizeof(int), 1, input_file);
        coded_symbols->codes[decoding_symbol] = calloc(coded_symbols->codes_lengths[decoding_symbol] / 8 + 1, sizeof(char));
        fread(coded_symbols->codes[decoding_symbol], sizeof(char), coded_symbols->codes_lengths[decoding_symbol] / 8 + 1, input_file);
    }
}