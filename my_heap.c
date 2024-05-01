#include "my_heap.h"

void swapping(Heap *heap, int index, int n) {
    int min = index;
    int left = min * 2 + 1, right = min * 2 + 2;
    if (left < n && heap->Nodes[left]->frequency < heap->Nodes[min]->frequency)
        min = left;
    if (right < n && heap->Nodes[right]->frequency < heap->Nodes[min]->frequency)
        min = right;
    if (min != index) {
        TreeNode *temp = heap->Nodes[index];
        heap->Nodes[index] = heap->Nodes[min];
        heap->Nodes[min] = temp;
        swapping(heap, min, n);
    }
}

void siftUp(Heap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->Nodes[index]->frequency < heap->Nodes[parent]->frequency) {
            TreeNode *temp = heap->Nodes[index];
            heap->Nodes[index] = heap->Nodes[parent];
            heap->Nodes[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}