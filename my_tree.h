#ifndef NSU_PTU_MY_TREE_H
#define NSU_PTU_MY_TREE_H

#include "my_heap.c"
#include <stdlib.h>
#include <unistd.h>

#define SEYCHAS_RVANYOOOOOT 9000000000000000000

#define TIME_FOR_SLEEP 1

void NewTreeNodeFromSymbol(TreeNode *initialisable, unsigned char symbol, long long int frequency);

void NewTreeNodeFromTwoTrees(TreeNode *initialisable, TreeNode *left, TreeNode *right);

TreeNode *build_Huffman_tree(long long int *frequencies, int unique_symbols_count);

void tree_destructor(TreeNode *current_node);

#endif
