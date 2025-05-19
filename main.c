#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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
int main(void) {
    char filename[100];

    printf("\t\t\tHuffman File Compressor\n");
    printf("Welcome to the Huffman File Compressor!\n");
    printf("To proceed further, please enter the name of the file you want to compress and ensure that it is in the same directory as this program.\n");

    get_and_validate_input_file(filename);

    printf("The file is validated now, you can proceed for further operations.\n");
    printf("Press Enter to continue...\n");
    getchar(); // wait for Enter

    return 0;
}
