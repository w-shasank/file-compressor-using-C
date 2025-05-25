#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "headerfile.h"



// Function to get and validate input file name
void get_and_validate_input_file(char *filename) {
    printf("Enter the name of the input file (e.g., input.txt): ");
    scanf("%s", filename);
    getchar();

    // Check if the file exists
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("E R R O R : File '%s' not found in the current directory.\n", filename);
        exit(0); 
    }
    fclose(file);
}
void after_validation_menu( char * filename) {
    printf("1.COnvert to Binary\n");
    printf("2. Compress File\n");
    printf("3. Decompress File\n");
    printf("4. Exit\n");
    int choice;
    printf("Please select an option to proceed further: ");
    scanf("%d", &choice);
    getchar(); // consume newline character
    switch (choice) {
        case 1:
            printf("Converting to binary...\n");
            sleep(2);
            write_to_binary_file(filename, "output.bin");
            break;
        case 2:
            printf("Compressing file...\n");
            sleep(1);
            printf("Compressing file...\n");
            sleep(1);
            printf("Compressing file...\n");
            sleep(1);
            compress_huffman("output.bin","compressed_ouput.bin");
            printf("File compressed successfully to 'compressed_output.bin'.\n");
            after_validation_menu(filename); // Return to the menu after compression
            break;
        case 3:
            printf("Decompressing file...\n");
            sleep(1);
            printf("Decompressing file...\n");
            sleep(1);
            printf("Decompressing file...\n");
            sleep(1);
            decompress_huffman("compressed_output.bin");
            printf("\nFile decompressed successfully to 'decompressed_output.txt'.\n");
             decompress_huffman("compressed_output.bin");
            printf("You can now view the decompressed file 'decompressed_output.txt'.\n");
            break;

        case 4:
            printf("Exiting...\n");
            sleep(1);
            exit(0);
        default:
          system("clear");
            printf("Invalid choice. Please try again.\n");
            sleep(1);
            system("clear");
            after_validation_menu(filename);
    }
    
}

    void write_to_binary_file(const char *input_filename, const char *output_filename) {
    FILE *in = fopen(input_filename, "r");
    if (in == NULL) {
        printf("Error opening input file '%s'\n", input_filename);
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(output_filename, "wb");
    if (out == NULL) {
        printf("Error creating output file '%s'\n", output_filename);
        fclose(in);
        exit(0);
    }

    int ch;
    unsigned char buffer = 0;
    int bit_count = 0;

   while ((ch = fgetc(in)) != EOF) {
    for (int i = 7; i >= 0; i--) {
        char bit_char = ((ch >> i) & 1) ? '1' : '0';
        fputc(bit_char, out);
    }
}

   // Handle any remaining bits properly
    if (bit_count > 0) {
        buffer <<= (8 - bit_count); 
        fwrite(&buffer, 1, 1, out);
    }
    // Printing size of the files
    fseek(in, 0L, SEEK_END);
    long input_size = ftell(in);
    fseek(out, 0L, SEEK_END);
    long output_size = ftell(out);

    fclose(in);
    fclose(out);
    printf("  Successfully wrote content of '%s' to binary file '%s' as actual bits.\n", input_filename, output_filename);
    printf(" Input File: %ld bytes (%ld bits)\n", input_size, input_size * 8);
    printf(" Output File: %ld bytes (%ld bits)\n", output_size, output_size * 8);
    printf("\n\n\n");
    printf("Press Enter to return to the menu...\n");
    getchar(); 
    system("clear");
    after_validation_menu("input.txt"); 
}
