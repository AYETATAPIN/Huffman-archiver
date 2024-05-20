#include "folder_handling.h"

void folder_handling(char *input_folder_name, char option) {
    DIR *input_folder = opendir(input_folder_name);
    struct dirent *current_file_dirent;
    FILE *current_file;
    while ((current_file_dirent = readdir(input_folder))) {
        if (strcmp(current_file_dirent->d_name, ".") == 0)
            continue;
        if (strcmp(current_file_dirent->d_name, "..") == 0)
            continue;
        char *current_file_name = calloc(1002, sizeof(int));
        memcpy(current_file_name, input_folder_name, sizeof(char) * (strlen(input_folder_name) + 1));
        strcat(current_file_name, "\\");
        strcat(current_file_name, current_file_dirent->d_name);
        if (option == 'C') {
            current_file = fopen(current_file_name, "rb");
            if (current_file == NULL) {
                printf("Embedded folder found, compressing\n");
                folder_handling(current_file_name, option);
                goto file_closing;
            }
            compression(current_file, current_file_name);
            printf("File ""%s"" compressed\n", current_file_name);
            fclose(current_file);
            remove(current_file_name);
        } else {
            DIR *checking_dir;
            for (int i = 0; i < strlen(current_file_name); ++i) {
                if (strcmp(current_file_name + i, output_file_extension) == 0) {
                    current_file = fopen(current_file_name, "rb");
                    if (current_file == NULL) {
                        printf("Embedded folder found, decompressing\n");
                        folder_handling(current_file_name, option);
                        goto file_closing;
                    }
                    decompression(current_file, current_file_name);
                    printf("File ""%s"" decompressed\n", current_file_name);
                    fclose(current_file);
                    remove(current_file_name);
                    break;
                } else if ((checking_dir = opendir(current_file_name)) != NULL) {
                    printf("Embedded folder found, decompressing\n");
                    folder_handling(current_file_name, option);
                    goto file_closing;
                }
            }
        }
        file_closing:;
    }
}
