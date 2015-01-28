// Original Author: Trevor Killeen (2015)

#include <stdio.h>
#include "./hufftree.h"

// helper function declarations
static char **gen_tree_map(struct huffman_node *root); 

int construct_tree(unsigned long *freqs, unsigned int len,
    struct huffman_node **root) {
  return 0; 
}

void free_tree(struct huffman_node *root) {
}

int compress_tree_to_file(struct huffman_node *root, FILE *file,
    int offset) {
  return 0;
}

int decompress_tree_from_file(FILE *file, int offset,
    struct huffman_node **root) {
  return 0;
}

int compress_file_using_tree(struct huffman_node *root, FILE *input,
    FILE *output, int offset) {
  return 0;
}

// Generate a mapping from character to string representation of
// the compressed bit sequence for that character according to
// the specified Huffman Tree
static char **gen_tree_map(struct huffman_node *root) {
  return NULL;
}

int reconstruct_file_using_tree(struct huffman_node *root, FILE *input,
    FILE *output, int offset) {
  return 0;
}
