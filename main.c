#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "headerfile.h"




int main(void) {
    char filename[100];

    printf("\t\t\tHuffman File Compressor\n");
    printf("Welcome to the Huffman File Compressor!\n");
    printf("To proceed further, please enter the name of the file you want to compress and ensure that it is in the same directory as this program.\n");

    //function to get and validate the input file
    get_and_validate_input_file(filename);

    printf("The file is validated now, you can proceed for further operations.\n");
    printf("Press Enter to continue...\n");
    getchar(); // wait for Enter
    system("clear");
    // Call the function to display the menu after validation
    
    after_validation_menu(filename);

    return 0;
}


 