#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "headerfile.h"
// Inserting a node into the huffman min-heap
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

