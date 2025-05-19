#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

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
            printf("Invalid choice. Please try again.\n");
            after_validation_menu(filename);
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
    after_validation_menu(filename);

    return 0;
}
