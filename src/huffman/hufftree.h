// Original Author: Trevor Killeen (2015)

#ifndef _HUFFTREE_H_
#define _HUFFTREE_H_

#include <stdbool.h>

/**
 * This header file defines various operations related to
 * generating a Huffman Tree from a list of character frequencies
 * and using that Huffman Tree to compress a file.
 */

struct huffman_node {
  bool internal;        // is the node an internal node
  long freq;            // frequency of the character at this node
                        // if not an internal node
  char val;             // char associated with this node if not
                        // an internal node
  huffman_node *left;   // left child
  huffman_node *right;  // right child
};

/*
 * Constructs a Huffman Tree from the specified frequency array.
 * Assumes that freqs[i] = the frequency of the character with
 * ASCII value i. 
 *
 * @param freqs the frequency array.
 * @param len the length of the frequency array.
 * @param root output parameter for the root of the Huffman Tree. It
 * is the client's responsibility to free the memory associated with
 * this tree by calling the appropriate API function.
 *
 * @return 0 on success, otherwise error.
 */
int construct_tree(unsigned long *freqs, unsigned int len,
  struct huffman_node **root);

/**
 * Frees the memory associated with the passed Huffman Tree.
 *
 * @param root the root of the tree to free.
 */
void free_tree(struct huffman_node *root);

/**
 * Writes the specified Huffman Tree to the specified file in a
 * compressed form at the specified offset. 
 *
 * @param root the root of the tree to write/compress.
 * @param file the file to write to.
 * @param offset the offset within the file to write the compressed
 * tree to.
 *
 * @return 0 if the tree is successfully written, otherwise error.
 */
int compress_tree_to_file(struct huffman_node *root, FILE *file,
  int offset);

/**
 * Reconstructs the specified Huffman Tree from the specified file
 * at the specified offset.
 *
 * @param file the file to read from.
 * @param offset the offset within the file to read the compressed
 * tree from.
 * @param root output parameter to store the reconstructed tree.
 *
 * @return 0 if the tree is successfully reconstructed, otherwise error.
 */
int decompress_tree_from_file(FILE *file, int offset,
  struct huffman_node **root);

int compress_file_using_tree(struct huffman_node *root, FILE *input,
  FILE *output, int offset);

int reconstruct_file_using_tree(struct huffman_node *root, FILE *input,
  FILE *output, int offset);

#endif
