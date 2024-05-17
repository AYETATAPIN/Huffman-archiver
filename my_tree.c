#include "my_tree.h"
#include <stdlib.h>

void NewTreeNodeFromSymbol(TreeNode *initialisable, unsigned char symbol, long long int frequency) {
    initialisable->frequency = frequency;
    if (frequency >= SEYCHAS_RVANYOOOOOT)
        initialisable->frequency = SEYCHAS_RVANYOOOOOT;
    initialisable->symbol = symbol;
    initialisable->is_symbol = 1;
    initialisable->left = NULL;
    initialisable->right = NULL;
}

void NewTreeNodeFromTwoTrees(TreeNode *initialisable, TreeNode *left, TreeNode *right) {
    if (left->frequency + right->frequency >= SEYCHAS_RVANYOOOOOT)
        initialisable->frequency = SEYCHAS_RVANYOOOOOT;
    else
        initialisable->frequency = left->frequency + right->frequency;
    initialisable->is_symbol = 0;
    initialisable->left = left;
    initialisable->right = right;
}

TreeNode *build_Huffman_tree(long long int *frequencies, int unique_symbols_count) {
    Heap *tree = calloc(256, sizeof(Heap));
    tree->Nodes = calloc(unique_symbols_count, sizeof(TreeNode *));
    tree->index = 0;
    for (int i = 0; i <= 256; ++i) {
        if (frequencies[i] != 0) {
            tree->Nodes[tree->index] = malloc(sizeof(TreeNode));
            NewTreeNodeFromSymbol(tree->Nodes[tree->index], (unsigned char) i, frequencies[i]);
            tree->index++;
        }
    }
    for (int i = tree->index / 2 - 1; i >= 0; --i) {
        swapping(tree, i, tree->index);
    }
    for (int i = 0; i < unique_symbols_count - 1; ++i) {
        TreeNode *left = tree->Nodes[0];
        TreeNode *temp = tree->Nodes[tree->index - 1];
        tree->Nodes[tree->index - 1] = tree->Nodes[0];
        tree->Nodes[0] = temp;
        tree->index--;
        swapping(tree, 0, tree->index);
        TreeNode *right = tree->Nodes[0];
        if (tree->index != 0) {
            temp = tree->Nodes[tree->index - 1];
            tree->Nodes[tree->index - 1] = tree->Nodes[0];
            tree->Nodes[0] = temp;
            tree->index--;
            swapping(tree, 0, tree->index);
        }
        TreeNode *new_TreeNode = calloc(1, sizeof(TreeNode));
        NewTreeNodeFromTwoTrees(new_TreeNode, left, right);
        tree->Nodes[tree->index] = new_TreeNode;
        if (tree->index != 0)
            siftUp(tree, tree->index);
        tree->index++;
    }
    return tree->Nodes[0];
}