#include "huffman_compressing.h"
#include <stdio.h>

void decompression(FILE *input_file, char *input_file_name) {
    unsigned char current_symbol;
    char *input_file_data = calloc(4, sizeof(char));
    input_file_data[3] = '\0';
    int all_symbols_ct = 0, current_code_capacity = 2, current_bit_index = 0, request_next = 0;
    int current_symbols_count = 0;
    int last_byte_index, last_byte_length;
    fread(&last_byte_index, sizeof(int), 1, input_file);
    fread(&last_byte_length, sizeof(int), 1, input_file);
    while (all_symbols_ct <= last_byte_index) {
        fread(&current_symbol, sizeof(char), 1, input_file);
        input_file_data[all_symbols_ct] = current_symbol;
        all_symbols_ct++;
        if (all_symbols_ct >= current_code_capacity) {
            current_code_capacity *= 2;
            input_file_data = realloc(input_file_data, sizeof(char) * current_code_capacity);
        }
    }
    sleep(TIME_FOR_SLEEP);
    printf("Decoding symbols\n");
    coded_symbols = malloc(sizeof(codes_for_symbols));
    coded_symbols->codes = calloc(sizeof(char *), 257);
    coded_symbols->codes_lengths = calloc(sizeof(int), 257);
    symbols_decoding(input_file);
    printf("Symbols decoded\n");
    fclose(input_file);
    sleep(TIME_FOR_SLEEP);
    printf("Writing decompressed information\n");
    char *output_file_name = calloc(strlen(input_file_name) - 10, sizeof(char));
    memcpy(output_file_name, input_file_name, sizeof(char) * (strlen(input_file_name) - 8));
    output_file_name[strlen(input_file_name) - 9] = '\0';
    FILE *output_file = fopen(output_file_name, "wb");
    while ((last_byte_index == -1 || current_bit_index <= last_byte_index * 8 + last_byte_length)) {
        symbols_searching:;
        if (last_byte_index != -1 && current_bit_index >= last_byte_index * 8 + last_byte_length) {
            current_bit_index += 1 * 48 * 8 + 8 * 4;
            break;
        }
        for (int i = 0; i <= 256; ++i) {
            if (coded_symbols->codes_lengths[i] != 0 && bitscmp(input_file_data, coded_symbols->codes[i], current_bit_index, coded_symbols->codes_lengths[i]) == 0) {
                char writing_symbol = (char) i;
                fwrite(&writing_symbol, sizeof(char), 1, output_file);
                current_bit_index += coded_symbols->codes_lengths[i];
                request_next += coded_symbols->codes_lengths[i];
                current_symbols_count++;
                if (request_next >= 8) {
                    request_next = 0;
                    break;
                }
                goto symbols_searching;
            }
        }
    }
    printf("Decompressed information written\n");
    free(input_file_data);
    free(output_file_name);
    for (int i = 0; i <= 256; ++i) {
        if (coded_symbols->codes[i] != NULL)
            free(coded_symbols->codes[i]);
    }
    free(coded_symbols->codes_lengths);
    free(coded_symbols);
    sleep(TIME_FOR_SLEEP);
}
