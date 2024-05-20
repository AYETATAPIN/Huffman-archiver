#include "huffman_compressing.h"
#include <stdio.h>

void compression(FILE *input_file, char *input_file_name) {
    printf("Calculating frequency\n");
    long long int *frequencies = calloc(257, sizeof(long long int));
    int unique_symbols_count = 0;
    long long int all_symbols_ct = 0;
    unsigned char current_symbol;
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        if (frequencies[current_symbol] == 0)
            unique_symbols_count++;
        if (frequencies[current_symbol] <= SEYCHAS_RVANYOOOOOT)
            frequencies[current_symbol]++;
        all_symbols_ct++;
    }
    sleep(TIME_FOR_SLEEP);
    printf("Frequency calculated\n");
    sleep(TIME_FOR_SLEEP);
    printf("Building Huffman Tree\n");
    TreeNode *root = build_Huffman_tree(frequencies, unique_symbols_count);
    printf("Coding symbols\n");
    sleep(TIME_FOR_SLEEP);
    coded_symbols = malloc(sizeof(codes_for_symbols));
    coded_symbols->codes = calloc(sizeof(char *), 257);
    coded_symbols->codes_lengths = calloc(sizeof(int), 257);
    char *code = calloc(3, sizeof(char));
    symbols_coding(root, code, 0, 2);
    tree_destructor(root);
    printf("Symbols coded\n");
    sleep(TIME_FOR_SLEEP);
    printf("Writing compressed information\n");
    char *output_file_name = calloc(strlen(input_file_name) + 10, sizeof(char));
    memcpy(output_file_name, input_file_name, sizeof(char) * strlen(input_file_name));
    strcat(output_file_name, output_file_extension);
    FILE *output_file = fopen(output_file_name, "wb");
    rewind(input_file);
    int current_bits_ct = 0, current_symbols_ct = 0;
    int last_byte_index = 0, last_byte_length = 0;
    fwrite(&last_byte_index, sizeof(int), 1, output_file);
    fwrite(&last_byte_length, sizeof(int), 1, output_file);
    unsigned char current_byte = 0;
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        for (int i = 0; i < coded_symbols->codes_lengths[current_symbol]; ++i) {
            current_byte |= (((coded_symbols->codes[current_symbol][i / 8] >> (i % 8)) & 1) << current_bits_ct);
            current_bits_ct++;
            if (current_bits_ct == 8) {
                fwrite(&current_byte, sizeof(char), 1, output_file);
                current_byte = 0;
                current_bits_ct = 0;
                current_symbols_ct++;
                last_byte_index++;
            }
        }
    }
    last_byte_length = current_bits_ct;
    if (current_bits_ct != 0)
        fwrite(&current_byte, sizeof(char), 1, output_file);
    for (int i = 0; i <= 256; ++i) {
        if (coded_symbols->codes_lengths[i] != 0) {
            current_symbol = (char) i;
            fwrite(&current_symbol, sizeof(char), 1, output_file);
            fwrite(&coded_symbols->codes_lengths[current_symbol], sizeof(int), 1, output_file);
            fwrite(coded_symbols->codes[current_symbol], sizeof(char), coded_symbols->codes_lengths[current_symbol] / 8 + 1, output_file);
        }
    }
    rewind(output_file);
    fwrite(&last_byte_index, sizeof(int), 1, output_file);
    fwrite(&last_byte_length, sizeof(int), 1, output_file);
    printf("Compressed information written\n");
    double compression_efficiency = (double) (((double) (1)) - ((double) ((double) current_symbols_ct / (double) all_symbols_ct))) * 100;
    printf("Compression efficiency: %lf %%\n", compression_efficiency);
    fclose(input_file);
    fclose(output_file);
    free(frequencies);
    free(code);
    free(output_file_name);
    for (int i = 0; i <= 256; ++i) {
        if (coded_symbols->codes[i] != NULL)
            free(coded_symbols->codes[i]);
    }
    free(coded_symbols->codes_lengths);
    free(coded_symbols);
    sleep(TIME_FOR_SLEEP);
}