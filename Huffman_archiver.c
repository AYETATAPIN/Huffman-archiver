#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "my_heap.c"

#define TIME_FOR_SLEEP 1

#define SEYCHAS_RVANYOOOOOT 9000000000000000000

typedef struct codes_for_symbols {
    char **codes;
    int *codes_lengths;
} codes_for_symbols;

codes_for_symbols *coded_symbols;


static char key_initialiser[] = "kirindenle_CBO_ZOV_ZV_1488_SMARTPHONE_VIVO"; // 42 symbols

static char last_byte_initialiser[] = "kirindenle_CBO_ZOV_ZV_09_11_2001_SMARTPHONE_VIVO"; // 48 symbols

static char output_file_extension[] = ".GOOOOOOL"; // 9 symbols

static int is_successfully_decompressed;

typedef union {
    char *bytes;
    int value;
} number;

void NewTreeNodeFromSymbol(TreeNode *initialisable, unsigned char symbol, long long int frequency) {
    initialisable->frequency = frequency;
    if (frequency >= SEYCHAS_RVANYOOOOOT)
        initialisable->frequency = SEYCHAS_RVANYOOOOOT;
    initialisable->symbol = symbol;
    initialisable->is_cymbol = 1;
    initialisable->left = NULL;
    initialisable->right = NULL;
}

void NewTreeNodeFromTwoTrees(TreeNode *initialisable, TreeNode *left, TreeNode *right) {
    if (left->frequency + right->frequency >= SEYCHAS_RVANYOOOOOT)
        initialisable->frequency = SEYCHAS_RVANYOOOOOT;
    else
        initialisable->frequency = left->frequency + right->frequency;
    initialisable->is_cymbol = 0;
    initialisable->left = left;
    initialisable->right = right;
}

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

int key_initialiser_cmp(char *str, int start) {
    for (int i = 0; i < 42; ++i) {
        if (str[start + i] != key_initialiser[i])
            return 1;
    }
    return 0;
}

int last_byte_keycmp(char *str, int start) {
    for (int i = 0; i < 48; ++i) {
        if (str[start + i] != last_byte_initialiser[i])
            return 1;
    }
    return 0;
}

void
symbols_coding(TreeNode *current_node, char *current_code, int current_code_index, int current_code_capacity) {
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
    if (current_node->is_cymbol == 1 && coded_symbols->codes_lengths[current_node->symbol] == 0) {
        coded_symbols->codes[current_node->symbol] = calloc(current_code_index, sizeof(char) * (current_code_index / 8 + 1));
        bitscpy(coded_symbols->codes[current_node->symbol], current_code, current_code_index);
        coded_symbols->codes_lengths[current_node->symbol] = current_code_index;
    }

}

TreeNode *build_Huffman_tree(long long int *frequencies, int unique_symbols_count) {
    Heap *tree = calloc(256, sizeof(Heap));
    tree->Nodes = calloc(unique_symbols_count, sizeof(TreeNode *));
    tree->index = 0;
    for (int i = 0; i <= 256; ++i) {
        if (frequencies[i] != 0) {
            tree->Nodes[tree->index] = malloc(sizeof(TreeNode));
            NewTreeNodeFromSymbol(tree->Nodes[tree->index], (unsigned char) i, frequencies[i]);
            tree->index++;
        }
    }
    for (int i = tree->index / 2 - 1; i >= 0; --i) {
        swapping(tree, i, tree->index);
    }
    for (int i = 0; i < unique_symbols_count - 1; ++i) {
        TreeNode *left = tree->Nodes[0];
        TreeNode *temp = tree->Nodes[tree->index - 1];
        tree->Nodes[tree->index - 1] = tree->Nodes[0];
        tree->Nodes[0] = temp;
        tree->index--;
        swapping(tree, 0, tree->index);
        TreeNode *right = tree->Nodes[0];
        if (tree->index != 0) {
            temp = tree->Nodes[tree->index - 1];
            tree->Nodes[tree->index - 1] = tree->Nodes[0];
            tree->Nodes[0] = temp;
            tree->index--;
            swapping(tree, 0, tree->index);
        }
        TreeNode *new_TreeNode = calloc(1, sizeof(TreeNode));
        NewTreeNodeFromTwoTrees(new_TreeNode, left, right);
        tree->Nodes[tree->index] = new_TreeNode;
        if (tree->index != 0)
            siftUp(tree, tree->index);
        tree->index++;
    }
    sleep(TIME_FOR_SLEEP);
    printf("Tree built\n");
    sleep(TIME_FOR_SLEEP);
    return tree->Nodes[0];
}

void compression(FILE *input_file, char *input_file_name) {
    printf("Calculating frequency\n");
    long long int *frequencies = calloc(257, sizeof(long long int));
    int unique_symbols_count = 0;
    long long int all_symbols_count = 0;
    unsigned char current_symbol;
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        if (frequencies[current_symbol] == 0)
            unique_symbols_count++;
        if (frequencies[current_symbol] <= SEYCHAS_RVANYOOOOOT)
            frequencies[current_symbol]++;
        all_symbols_count++;
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
    free(root);
    printf("Symbols coded\n");
    sleep(TIME_FOR_SLEEP);
    printf("Writing compressed information\n");
    char *output_file_name = calloc(strlen(input_file_name) + 10, sizeof(char));
    memcpy(output_file_name, input_file_name, sizeof(char) * strlen(input_file_name));
    strcat(output_file_name, output_file_extension);
    FILE *output_file = fopen(output_file_name, "wb");
    rewind(input_file);
    int current_bits_ct = 0, current_symbols_ct = 0;
    unsigned char current_byte = 0;
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        current_symbols_ct++;
        for (int i = 0; i < coded_symbols->codes_lengths[current_symbol]; ++i) {
            current_byte |= (((coded_symbols->codes[current_symbol][i / 8] >> (i % 8)) & 1) << current_bits_ct);
            current_bits_ct++;
            if (current_bits_ct == 8) {
                fwrite(&current_byte, sizeof(char), 1, output_file);
                current_byte = 0;
                current_bits_ct = 0;
            }
        }
    }
    if (current_bits_ct != 0) {
        fwrite(last_byte_initialiser, sizeof(char), 48, output_file);
        fwrite(&current_bits_ct, sizeof(int), 1, output_file);
        fwrite(&current_byte, sizeof(char), 1, output_file);
    }
    fwrite(key_initialiser, sizeof(char), 43, output_file);
    for (int i = 0; i <= 256; ++i) {
        if (coded_symbols->codes_lengths[i] != 0) {
            current_symbol = (char) i;
            fwrite(&current_symbol, sizeof(char), 1, output_file);
            fwrite(&coded_symbols->codes_lengths[current_symbol], sizeof(int), 1, output_file);
            fwrite(coded_symbols->codes[current_symbol], sizeof(char), coded_symbols->codes_lengths[current_symbol] / 8 + 1, output_file);
        }
    }
    printf("Compressed information written\n");
    fclose(input_file);
    fclose(output_file);
    free(frequencies);
    free(code);
    free(output_file_name);
    sleep(TIME_FOR_SLEEP);
}

void symbols_decoding(FILE *input_file, int key_initialiser_index) {
    rewind(input_file);
    unsigned char current_symbol;
    for (int i = 0; i <= key_initialiser_index + 42; ++i) {
        fread(&current_symbol, sizeof(char), 1, input_file);
    }
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        unsigned char decoding_symbol = current_symbol;
        fread(&coded_symbols->codes_lengths[decoding_symbol], sizeof(int), 1, input_file);
        coded_symbols->codes[decoding_symbol] = calloc(coded_symbols->codes_lengths[decoding_symbol] / 8 + 1, sizeof(char));
        fread(coded_symbols->codes[decoding_symbol], sizeof(char), coded_symbols->codes_lengths[decoding_symbol] / 8 + 1, input_file);
    }
}

void decompression(FILE *input_file, char *input_file_name) {
    printf("Searching for symbols key initialiser\n");
    is_successfully_decompressed = 0;
    unsigned char current_symbol;
    int key_found = 0;
    char *input_file_data = calloc(4, sizeof(char));
    input_file_data[3] = '\0';
    int all_symbols_ct = 0, current_code_capacity = 2, current_bit_index = 0, request_next = 0;
    int current_symbols_count = 0;
    while (fread(&current_symbol, sizeof(char), 1, input_file) != 0) {
        input_file_data[all_symbols_ct] = current_symbol;
        all_symbols_ct++;
        if (all_symbols_ct >= current_code_capacity) {
            current_code_capacity *= 2;
            input_file_data = realloc(input_file_data, sizeof(char) * current_code_capacity);
        }
    }
    int last_byte_length = -1, last_byte_index = -1, key_initialiser_index = -1;
    char *compressed_data = calloc(all_symbols_ct, sizeof(char));
    int compressed_data_ct = 0;
    for (int i = 0; i < all_symbols_ct; ++i) {
        if (input_file_data[i] == 'k') {
            if (last_byte_keycmp(input_file_data, i) == 0) {
                last_byte_index = i;
                i += 48;
                current_symbol = input_file_data[i];
                last_byte_length = input_file_data[i];
                i += 4;
            } else if (key_initialiser_cmp(input_file_data, i) == 0) {
                key_found = 1;
                key_initialiser_index = i;
                break;
            }
        }
        compressed_data[compressed_data_ct] = input_file_data[i];
        compressed_data_ct++;
        current_symbol = input_file_data[i];

    }
    if (key_found == 0)
        return;
    sleep(TIME_FOR_SLEEP);
    printf("Key initialiser found\n");
    sleep(TIME_FOR_SLEEP);
    printf("Decoding symbols\n");
    coded_symbols = malloc(sizeof(codes_for_symbols));
    coded_symbols->codes = calloc(sizeof(char *), 257);
    coded_symbols->codes_lengths = calloc(sizeof(int), 257);
    symbols_decoding(input_file, key_initialiser_index);
    printf("Symbols decoded\n");
    fclose(input_file);
    sleep(TIME_FOR_SLEEP);
    printf("Writing decompressed information\n");
    char *output_file_name = calloc(strlen(input_file_name) - 10, sizeof(char));
    memcpy(output_file_name, input_file_name, sizeof(char) * (strlen(input_file_name) - 8));
    output_file_name[strlen(input_file_name) - 9] = '\0';
    FILE *output_file = fopen(output_file_name, "wb");
    while ((last_byte_index == -1 || current_bit_index / 8 + 1 <= last_byte_index) && (current_bit_index / 8 < key_initialiser_index)) {
        symbols_searching:;
        if (last_byte_index != -1 && current_bit_index >= last_byte_index * 8 + last_byte_length) {
            current_bit_index += 1 * 48 * 8 + 8 * 4;
            break;
        }
        for (int i = 0; i <= 256; ++i) {
            if (coded_symbols->codes_lengths[i] != 0 && (last_byte_index == -1 || coded_symbols->codes_lengths[i] + current_bit_index <= last_byte_index * 8 + last_byte_length) && bitscmp(compressed_data, coded_symbols->codes[i], current_bit_index, coded_symbols->codes_lengths[i]) == 0) {
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
    is_successfully_decompressed = 1;
    printf("Decompressed information written\n");
    free(input_file_data);
    free(input_file_name);
    free(compressed_data);
    sleep(TIME_FOR_SLEEP);

}

int main() {
    char *input_file_name = calloc(1002, sizeof(char));
    FILE *input_file;
    file_opening:;
    printf("Enter a file name: ");
    scanf("%s", input_file_name);
    input_file = fopen(input_file_name, "rb");
    if (input_file == NULL) {
        printf("No such file or directory found. Are you sure you specified file extension?\n");
        goto file_opening;
    }
    printf("Such file exists.\n");
    char option;
    option_choosing:;
    printf("Pick an option to compress or decompress the file (C / D): ");
    scanf("%c", &option);
    if (option == '\n')
        scanf("%c", &option);
    if (option == 'C') {
        printf("Compressing\n");
        compression(input_file, input_file_name);
        printf("File compressed successfully\n");
    } else if (option == 'D') {
        printf("Decompressing\n");
        decompression(input_file, input_file_name);
        if (is_successfully_decompressed == 0) {
            printf("An error occured during decompression\n");
            exit(666);
        }
        printf("File Decompressed successfully\n");
    } else {
        printf("No such option, C - compress, D - decompress\n");
        goto option_choosing;
    }
    printf("Do you want to see codes for each symbol? (Y / N): ");
    codes_showing:;
    scanf("%c", &option);
    if (option == 'Y') {
        printf("Codes for symbols:\n");
        for (int i = 0; i <= 256; ++i) {
            if (coded_symbols->codes_lengths[i] != 0) {
                printf("%c %d %d ", i, i, coded_symbols->codes_lengths[i]);
                for (int j = 0; j < coded_symbols->codes_lengths[i]; ++j) {
                    printf("%d", (coded_symbols->codes[i][j / 8] >> (j % 8)) & 1);
                }
                printf("\n");
            }
        }
    } else if (option != 'N')
        goto codes_showing;
    for (int i = 0; i <= 256; ++i) {
        if (coded_symbols->codes[i] != NULL)
            free(coded_symbols->codes[i]);
    }
    printf("Thank you for using this archiver!");
    return 0;
}