#include "binary_trees.h"

/**
 * binary_tree_height - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree.
 *
 * Return: The height of the tree, or 0 if tree is NULL.
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
	size_t left_height, right_height;

	if (tree == NULL)
		return (0);

	left_height = binary_tree_height(tree->left);
	right_height = binary_tree_height(tree->right);

	return (1 + (left_height > right_height ? left_height : right_height));
}

/**
 * heap_insert - Inserts a value in a Max Binary Heap.
 * @root: A double pointer to the root node of the Heap.
 * @value: The value to store in the node to be inserted.
 *
 * Return: A pointer to the created node, or NULL on failure.
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;

	new_node = binary_tree_node(NULL, value);
	if (!new_node)
		return (NULL);

	if (*root == NULL)
	{
		*root = new_node;
		return (new_node);
	}

	parent = *root;

	while (parent && binary_tree_height(parent->left) > 0)
	{
		if (binary_tree_height(parent->left) > 0 &&
			binary_tree_height(parent->right) == 0)
			parent = parent->right;
		else if (binary_tree_height(parent->left) ==
			binary_tree_height(parent->right) &&
			parent->left->left == NULL)
			parent = parent->left->left;
		else
			break;
	}

	new_node->parent = parent;
	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		int temp = new_node->n;
		new_node->n = new_node->parent->n;
		new_node->parent->n = temp;
		new_node = new_node->parent;
	}

	return (new_node);
}

