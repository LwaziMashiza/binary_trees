#include <stddef.h>
#include "binary_trees.h"

/**
 * heap_to_sorted_array - Converts a Binary Max Heap to a sorted array of integers
 * @heap: Pointer to the root node of the heap to convert
 * @size: Address to store the size of the array
 *
 * Return: Pointer to the sorted array of integers.
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
    int *sorted_array = NULL;
    size_t i, heap_size;

    if (!heap || *size == 0)
        return (NULL);

    /* Calculate the size of the heap using a loop */
    for (i = 0, heap_size = 0; heap_size < *size; i++)
    {
        int value = heap_extract(&heap);
        if (value != 0)
            heap_size++;
    }

    /* Reset the heap to its original state */
    while (i > 0)
    {
        heap_insert(&heap, sorted_array[i - 1]);
        i--;
    }

    if (heap_size > 0)
    {
        sorted_array = malloc(sizeof(int) * heap_size);
        if (!sorted_array)
            return (NULL);

        for (i = 0; i < heap_size; i++)
        {
            sorted_array[i] = heap_extract(&heap);
        }
    }

    *size = heap_size;
    return (sorted_array);
}

