#ifndef NSU_PTU_MY_HEAP_H
#define NSU_PTU_MY_HEAP_H

typedef struct TreeNode {
    long long int frequency;
    unsigned char symbol;
    int is_cymbol;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct Heap {
    struct TreeNode **Nodes;
    int index;
} Heap;

void swapping(Heap *heap, int index, int n);

void siftUp(Heap *heap, int index);

#endif