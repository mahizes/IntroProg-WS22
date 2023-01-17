#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elemements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des Letzten Elements (Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
    // calculate the length of the temporary array
    int len = last - first + 1;
    int temp[len]; // create a temporary array

    // initial pointers for the left and right subarrays
    int i = first;  
    int j = middle + 1;
    int k = 0;

    // iterate through both subarrays and compare elements
    while (i <= middle && j <= last) {
        if (array[i] <= array[j]) {
            temp[k] = array[i];
            i++;
        } else {
            temp[k] = array[j];
            j++;
        }
        k++;
    }

    // copy the remaining elements from the left subarray
    while (i <= middle) {
        temp[k] = array[i]; 
        i++;
        k++;
    }

    // copy the remaining elements from the right subarray
    while (j <= last) {
        temp[k] = array[j];    
        j++;
        k++;
    }

    // copy the sorted elements from the temporary array back to the original array
    for (i = 0; i < len; i++) {
        array[first + i] = temp[i]; // first + i is the index of the original array
    }
}


/*
 * Diese Funktion implementiert den iterativen Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array:  Pointer auf das Array
 * last :  Index des letzten Elements
 */
void merge_sort(int* array, int last)
{
    int step = 1;   // length of the subarrays
    
    while (step <= last) {
        int left = 0;   // index of the left subarray

        while (left <= last - step) {
            int middle = left + step - 1;
            middle = (middle < last) ? middle : last;
            int right = left + 2*step - 1;
            right = (right < last) ? right : last;
            merge(array, left, middle, right);
            left += 2*step;
        }
        step *= 2;
    }
}  

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_iterativ <maximale anzahl> \
 * 	   <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    int max_len = atoi(argv[1]);
    int *array = (int *)malloc(sizeof(int) * max_len);
    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    merge_sort(array, len - 1);

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);
    array = NULL;

    return 0;
}
