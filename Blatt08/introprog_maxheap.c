#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"


heap* heap_create(size_t capacity) {

    //  Allocate memory for the heap struct and initialize variables
    heap* h = (heap*) malloc(sizeof(heap));
    h->capacity = capacity;     //  Set the maximum capacity of the heap
    h->size = 0;        // Initialize the current number of elements in the heap to 0
    h->elements = (int*) malloc(sizeof(int) * capacity);    //  Allocate memory for the elements of the heap
    return h;
}

void heapify(heap* h, size_t i) {

    size_t largest = i;     //  Initialize largest element as the root element
    size_t left = 2 * i + 1;    // Calculate the left child of the root element    
    size_t right = 2 * i + 2;   // Calculate the right child of the root element

    // Check if the left child is larger than the root element
    if (left < h->size && h->elements[left] > h->elements[largest]) {
        largest = left;
    }

    // Check if the right child is larger than the root element
    if (right < h->size && h->elements[right] > h->elements[largest]) {
        largest = right;
    }

    // If the largest element is not the root element, swap them and call heapify again
    if (largest != i) {
        int temp = h->elements[i];
        h->elements[i] = h->elements[largest];
        h->elements[largest] = temp;
        heapify(h, largest);
    }
}

int heap_extract_max(heap* h) {

    // If the heap is empty, return -1
    if (h->size == 0) {
        return -1;
    }

    int max = h->elements[0];       // Store the max element (root) in a variable
    h->elements[0] = h->elements[h->size - 1];      // Replace the root with the last element in the heap
    h->size--;      // Decrement the size of the heap
    heapify(h, 0);  // Re-heapify the tree to maintain the heap property
    return max;    // Return the max element
}

int heap_insert(heap* h, int key) {

    // Return -1 if heap is full
    if (h->size == h->capacity) {
        return -1;
    }

    // Add the new key to the end of the heap
    h->elements[h->size] = key;
    int i = h->size;
    h->size++;

    // Compare new key with its parent and swap if necessary
    while (i != 0 && h->elements[(i - 1) / 2] < h->elements[i]) {
        int temp = h->elements[i];
        h->elements[i] = h->elements[(i - 1) / 2];
        h->elements[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    return 0;
}

void heap_free(heap* h) {
    free(h->elements);  // Free memory allocated for elements in the heap
    free(h);    // Free memory allocated for the heap struct
} 