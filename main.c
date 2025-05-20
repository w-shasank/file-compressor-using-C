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
            // Call the function to compress the file
            break;
        case 3:
            printf("Decompressing file...\n");
            sleep(1);
            printf("Decompressing file...\n");
            sleep(1);
            printf("Decompressing file...\n");
            sleep(1);
             //add the function to decompress the file

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
 void compress_huffman(const char *binary_filename, const char *compressed_filename) 
 {
    FILE *binary_input =fopen(binary_filename, "rb");
    if (binary_input == NULL) {
        printf("Error opening the binary file '%s'\n", binary_filename);
        printf("Please create a binary ouput file first.\n");
        printf("Returning to the lobby......\n");
        sleep(2);
        return  0;
    }
    int frequencies[256] = {0};
    int ch;
    while ((ch = fgetc(binary_input)) != EOF)
     {
    frequencies[ch]++;
   }
fclose(binary_input);
   
   FILE *compressed_output = fopen(compressed_filename, "wb");
    if (compressed_output == NULL) {
        printf("Error creating compressed file '%s'\n", compressed_filename);
        fclose(binary_input);
        return 0;
    }

 }
int main(void) {
    char filename[100];

    printf("\t\t\tHuffman File Compressor\n");
    printf("Welcome to the Huffman File Compressor!\n");
    printf("To proceed further, please enter the name of the file you want to compress and ensure that it is in the same directory as this program.\n");

    get_and_validate_input_file(filename);

    printf("The file is validated now, you can proceed for further operations.\n");
    printf("Press Enter to continue...\n");
    getchar(); // wait for Enter
    system("clear");
    after_validation_menu(filename);

    return 0;
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
        exit(EXIT_FAILURE);
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

   // Handle any remaining bits
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
}


 