#include "minHeap.h"

#include <stdlib.h>

struct Edge {
    int to;
    int weight;
};

struct MinHeap {
    struct Edge* data;
    int size;
    int capacity;
};

MinHeap* createMinHeap(int initialCapacity)
{
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap)
        return NULL;

    heap->capacity = initialCapacity > 0 ? initialCapacity : 16;
    heap->size = 0;
    heap->data = (struct Edge*)malloc(heap->capacity * sizeof(struct Edge));

    return heap;
}

static void swap(struct Edge* a, struct Edge* b)
{
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

void pushHeap(MinHeap* heap, int to, int weight)
{
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (struct Edge*)realloc(heap->data, heap->capacity * sizeof(struct Edge));
    }

    int i = heap->size;
    heap->data[i].to = to;
    heap->data[i].weight = weight;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2].weight > heap->data[i].weight) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool popHeap(MinHeap* heap, int* outTo, int* outWeight)
{
    if (heap->size <= 0)
        return false;

    *outTo = heap->data[0].to;
    *outWeight = heap->data[0].weight;

    if (heap->size == 1) {
        heap->size--;
        return true;
    }

    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    int i = 0;
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left].weight < heap->data[smallest].weight)
            smallest = left;

        if (right < heap->size && heap->data[right].weight < heap->data[smallest].weight)
            smallest = right;

        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }

    return true;
}

bool isHeapEmpty(MinHeap* heap)
{
    if (!heap)
        return true;
    return heap->size == 0;
}

void freeMinHeap(MinHeap* heap)
{
    if (heap) {
        free(heap->data);
        free(heap);
    }
}