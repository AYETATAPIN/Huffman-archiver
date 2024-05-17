#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "folder_handling.c"

#define TIME_FOR_SLEEP 1

#define SEYCHAS_RVANYOOOOOT 9000000000000000000

codes_for_symbols *coded_symbols;

int main() {
    char *input_folder_name = calloc(1002, sizeof(char));
    char option;
    DIR *input_folder;
    printf("Enter a folder name. If you want to change a single file, type ""F"": ");
    folder_opening:;
    scanf("%s", input_folder_name);
    if (strcmp(input_folder_name, "F") == 0)
        goto file;
    if (NULL == (input_folder = opendir(input_folder_name))) {
        printf("No such directory found. Are you sure you provided absolute path?\n");
        goto folder_opening;
    }
    printf("Such folder exists.\n");
    folder_option_choosing:;
    printf("Pick an option to compress or decompress the files (C / D): ");
    scanf("%c", &option);
    if (option == '\n')
        scanf("%c", &option);
    if (option == 'C') {
        printf("Compressing\n");
    } else if (option == 'D') {
        printf("Decompressing\n");
    } else {
        printf("No such option, C - compress, D - decompress\n");
        goto folder_option_choosing;
    }
    closedir(input_folder);
    folder_handling(input_folder_name, option);
    printf("Thank you for using this archiver!\n");
    goto end;
    file:;
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
    file_option_choosing:;
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
        printf("File Decompressed successfully\n");
    } else {
        printf("No such option, C - compress, D - decompress\n");
        goto file_option_choosing;
    }
    printf("Thank you for using this archiver!\n");
    end:;
    scanf("%c", &option);
    while (scanf("%c", &option) == -1 && option == '\n') {
    }
    return 0;
}