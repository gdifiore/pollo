/*
 *
 * pollo.c - pollo
 *
 * (c) 2018 gdifiore <difioregabe@gmail.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../include/pollo.h"

size_t read_size;
unsigned char object_buffer[16];
int i, c, offset;

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("[!] Error: No file\n");
        printf("Usage: %s <file path> <start offset>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    else if (argc == 2) {
        printf("[!] Error: No start offset (0 = dump whole file)\n");
        printf("Usage: %s <file path> <start offset>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    } 
    else if (argc > 3) {
        printf("[!] Error: Too many arguments\n");
        printf("Usage: %s <file path> <start offset>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if (argc == 3) {
        const char *file_path = argv[1];
        FILE *object_file = fopen(file_path, "r");

        if (object_file == NULL) {
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        } 
        else {
            offset = atoi(argv[2]);
            hexdump(object_file, offset);
        }
        return 0; 
    }

    return 0;
}

void hexdump(FILE *object_file, int start_offset) {
    fseek(object_file, start_offset, SEEK_SET); // what we do here is go back back back back
    offset = 0;
    while ((read_size = fread(object_buffer, 1, sizeof object_buffer, object_file)) > 0) {
        printf("%04x ", offset);
        offset += 16; // chunks
        for (i = 0; i < 16; i++) {
            printf("%02x ", object_buffer[i]);
        }
        for (i = 0; i < 16; i++) {
            c = object_buffer[i];
            printf("%c", (c >= 33 && c <= 255?c:'.')); // pad with dots
        }
        printf("\n"); 
    }
    fclose(object_file); // close file
    return; 
}