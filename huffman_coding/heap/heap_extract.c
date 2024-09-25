#include "heap.h"
#include "binary_tree_utils.h"
#include <stdlib.h>

/**
 * minHeapSiftDown - Restores Min Binary Heap properties of a tree by sifting swapped data
 *   down from root position.
 *
 * @root: pointer to Min Binary Heap root node
 * @data_cmp: data comparison function pointer
 */
void minHeapSiftDown(binary_tree_node_t *root,
                     int (data_cmp)(void *, void *))
{
    binary_tree_node_t *temp = NULL, *next = NULL;
    void *swap;

    if (!data_cmp)
        return;

    temp = root;
    while (temp && temp->left)
    {
        if (!temp->right ||
            data_cmp(temp->left->data, temp->right->data) <= 0)
        {
            if (data_cmp(temp->data, temp->left->data) >= 0)
                next = temp->left;
            else
                break;
        }
        else if (data_cmp(temp->data, temp->right->data) >= 0)
            next = temp->right;
        else
            break;

        if (next)
        {
            swap = temp->data;
            temp->data = next->data;
            next->data = swap;
        }

        temp = next;
    }
}

/**
 * heapExtract - extracts the value at the root of a Min Binary Heap
 *
 * @root: pointer to Min Binary Heap root node
 * @data_cmp: data comparison function pointer
 * Return: pointer to data from root node of binary heap
 */
void *heapExtract(binary_tree_node_t **root,
                  int (data_cmp)(void *, void *))
{
    binary_tree_node_t *last = NULL;
    void *extract = NULL;

    if (!root || !data_cmp)
        return (NULL);

    last = lastInLevelOrder(*root);
    if (!last)
        return (NULL);

    extract = (*root)->data;
    (*root)->data = last->data;

    minHeapSiftDown(*root, data_cmp);

    if (last->parent)
    {
        if (last->parent->left == last)
            last->parent->left = NULL;
        else if (last->parent->right == last)
            last->parent->right = NULL;
    }

    if (last == *root)
        *root = NULL;
    free(last);

    return (extract);
}

/**
 * heap_extract - wraps heapExtract to interface with Binary Heaps contained
 *   in a `heap_t` structure
 *
 * @heap: pointer to a heap_t binary heap profile structure
 * Return: pointer to data from root node of binary heap
 */
void *heap_extract(heap_t *heap)
{
    void *extract = NULL;

    if (!heap || !heap->data_cmp || !heap->root)
        return (NULL);

    extract = heapExtract(&(heap->root), heap->data_cmp);
    if (extract != NULL)
        heap->size--;

    return (extract);
}
