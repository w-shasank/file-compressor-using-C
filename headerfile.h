#ifndef HEADERFILE_H
#define HEADERFILE_H

// Huffman Tree Node
typedef struct HuffmanNode {
    unsigned char data;
    int freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

// Min-Heap for Huffman Nodes
typedef struct {
    HuffmanNode *nodes[256];
    int size;
} MinHeap;

// Function Prototypes
void get_and_validate_input_file(char *filename);
void after_validation_menu( char *filename);

void write_to_binary_file(const char *text_filename, const char *binary_filename);
void compress_huffman(const char *binary_filename, const char *compressed_filename);
void decompress_huffman(const char *compressed_filename);
void print_file_sizes(const char *file1, const char *file2);

void insert_heap(MinHeap *heap, HuffmanNode *node);
HuffmanNode* extract_min(MinHeap *heap);
void generate_codes(HuffmanNode *root, char *code, int depth, char codes[256][256]);
void decompress_huffman(const char *compressed_filename);
#endif // HEADERFILE_H
