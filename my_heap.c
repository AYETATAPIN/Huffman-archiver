#pragma once

#include <stdlib.h>
#include <string.h>
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

void pivition(char **arr, int left, int right) {
    if (left >= right)
        return;
    char *pivo = arr[rand() % (right - left) + left];
    int n = right - left;
    int svetloe_nefiltrovannoe = 0;
    char **less = malloc(sizeof(char) * n), less_ct = 0;
    char **greater = malloc(sizeof(char) * n), greater_ct = 0;
    for (int i = left; i < right; ++i) {
        if (strcmp(arr[i], pivo) < 0) {
            less[less_ct] = arr[i];
            less_ct++;
        } else if (strcmp(arr[i], pivo) > 0) {
            greater[greater_ct] = arr[i];
            greater_ct++;
        } else
            svetloe_nefiltrovannoe++;
    }
    for (int i = 0; i < less_ct; ++i) {
        arr[left + i] = less[i];
    }
    for (int i = 0; i < svetloe_nefiltrovannoe; ++i) {
        arr[left + less_ct + i] = pivo;
    }
    int zakuska_s_pivom = left + less_ct + svetloe_nefiltrovannoe;
    for (int i = 0; i < greater_ct; ++i) {
        arr[zakuska_s_pivom + i] = greater[i];
    }
    free(less);
    free(greater);
    pivition(arr, left, left + less_ct);
    pivition(arr, zakuska_s_pivom, right);
}
