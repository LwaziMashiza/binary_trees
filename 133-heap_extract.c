#include "binary_trees.h"

/**
 * heapify - Corrects the heap order property of a binary heap.
 * @root: Pointer to the root node of the heap.
 */
void heapify(heap_t *root) {
    heap_t *largest = root;
    heap_t *left = root->left;
    heap_t *right = root->right;

    if (left != NULL && left->n > largest->n) {
        largest = left;
    }

    if (right != NULL && right->n > largest->n) {
        largest = right;
    }

    if (largest != root) {
        int temp = root->n;
        root->n = largest->n;
        largest->n = temp;
        heapify(largest);
    }
}

/**
 * tree_height - Measures the height of a binary tree.
 * @tree: Pointer to the root node of the tree.
 * Return: Height of the tree or 0 if tree is NULL.
 */
size_t tree_height(const heap_t *tree) {
    size_t left_height, right_height;

    if (tree == NULL) {
        return 0;
    }

    left_height = tree_height(tree->left);
    right_height = tree_height(tree->right);

    return (left_height > right_height ? left_height + 1 : right_height + 1);
}

/**
 * get_last_node - Gets the last node in the last level of a binary heap.
 * @root: Pointer to the root of the heap.
 * @height: Height of the heap.
 * @index: Current level-order index.
 * @node: Pointer to the last node.
 */
void get_last_node(heap_t *root, size_t height, size_t index, heap_t **node) {
    if (root == NULL) {
        return;
    }

    if (height == index) {
        *node = root;
    }

    get_last_node(root->left, height, index + 1, node);
    get_last_node(root->right, height, index + 1, node);
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap.
 * @root: Double pointer to the root node of the heap.
 * Return: Value of the extracted root node, or 0 on failure.
 */
int heap_extract(heap_t **root) {
    if (root == NULL || *root == NULL) {
        return 0;
    }

    int value = (*root)->n;
    size_t height = tree_height(*root);
    heap_t *last_node = NULL;

    if (height > 0) {
        get_last_node(*root, height, 0, &last_node);
        if (last_node != *root) {
            // Replace the root with the last node
            (*root)->n = last_node->n;
            if (last_node->parent->left == last_node) {
                last_node->parent->left = NULL;
            } else {
                last_node->parent->right = NULL;
            }
        } else {
            // The last node is the root
            *root = NULL;
        }
        free(last_node);
        heapify(*root);
    } else {
        // The heap only contains the root
        free(*root);
        *root = NULL;
    }

    return value;
}

