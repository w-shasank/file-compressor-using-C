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
// Inserting a node into the min-heap
void insert_heap(MinHeap *heap, HuffmanNode *node) {
    int i = heap->size++;
    while (i && node->freq < heap->nodes[(i - 1) / 2]->freq) {
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->nodes[i] = node;
}

// Extracting node with minimum frequency
HuffmanNode* extract_min(MinHeap *heap) {
    HuffmanNode *min = heap->nodes[0];
    heap->nodes[0] = heap->nodes[--heap->size];
    int i = 0, smallest = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < heap->size && heap->nodes[left]->freq < heap->nodes[smallest]->freq)
            smallest = left;
        if (right < heap->size && heap->nodes[right]->freq < heap->nodes[smallest]->freq)
            smallest = right;
        if (smallest == i) break;

        HuffmanNode *temp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[smallest];
        heap->nodes[smallest] = temp;
        i = smallest;
    }

    return min;
}

// Generating  Huffman codes
void generate_codes(HuffmanNode *root, char *code, int depth, char codes[256][256]) {
    if (!root) return;

    if (!root->left && !root->right) {
        code[depth] = '\0';
        strcpy(codes[root->data], code);
        return;
    }

    code[depth] = '0';
    generate_codes(root->left, code, depth + 1, codes);
    code[depth] = '1';
    generate_codes(root->right, code, depth + 1, codes);
}

 void compress_huffman(const char *binary_filename, const char *compressed_filename) {
    FILE *in = fopen(binary_filename, "rb");
    if (!in) {
        perror("Error opening binary file");
        exit(1);
    }

    // Count frequency  for each byte
    int frequencies[256] = {0};
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        frequencies[ch]++;
    }
    rewind(in);

    //  Building Huffman Tree
    MinHeap heap = {.size = 0};
    for (int i = 0; i < 256; i++) {
        if (frequencies[i]) {
            HuffmanNode *node = malloc(sizeof(HuffmanNode));
            node->data = i;
            node->freq = frequencies[i];
            node->left = node->right = NULL;
            insert_heap(&heap, node);
        }
    }
    while (heap.size > 1) {
        HuffmanNode *left = extract_min(&heap);
        HuffmanNode *right = extract_min(&heap);
        HuffmanNode *merged = malloc(sizeof(HuffmanNode));
        merged->data = 0;
        merged->freq = left->freq + right->freq;
        merged->left = left;
        merged->right = right;
        insert_heap(&heap, merged);
    }
    HuffmanNode *root = extract_min(&heap);

    // Generate Huffman codes for each character
    char codes[256][256] = {0};
    char buffer[256];
    generate_codes(root, buffer, 0, codes);

    //  Write codes and compressed data to output
    FILE *out = fopen(compressed_filename, "wb");
    if (!out) {
        perror("Error opening output file");
        exit(1);
    }

    // Saving frequency table for decompression 
    fwrite(frequencies, sizeof(int), 256, out);

    // Encoding the input
    unsigned char byte = 0;
    int bit_count = 0;
    while ((ch = fgetc(in)) != EOF) {
        char *code = codes[ch];
        for (int i = 0; code[i]; i++) {
            byte = byte << 1 | (code[i] - '0');
            bit_count++;
            if (bit_count == 8) {
                fwrite(&byte, 1, 1, out);
                bit_count = 0;
                byte = 0;
            }
        }
    }
    if (bit_count > 0) {
        byte <<= (8 - bit_count);
        fwrite(&byte, 1, 1, out);
    }
    fclose(in);
    fclose(out);
    printf("Compression complete.\n");
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


 