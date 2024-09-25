#include "binary_tree_utils.h"
#include <stdlib.h>

size_t binaryTreeSize(const binary_tree_node_t *tree)
{
    if (!tree)
        return (0);

    if (!tree->left && !tree->right)
        return (1);

    return (1 + binaryTreeSize(tree->left) +
            binaryTreeSize(tree->right));
}

int binaryTreeIsComplete(const binary_tree_node_t *tree,
                         size_t node_i, size_t tree_sz)
{
    if (!tree)
        return (1);

    if (node_i >= tree_sz)
        return (0);

    return (binaryTreeIsComplete(tree->left, (2 * node_i) + 1, tree_sz) &&
            binaryTreeIsComplete(tree->right, (2 * node_i) + 2, tree_sz));
}

binary_tree_node_t *lastInLevelOrder(binary_tree_node_t *root)
{
    binary_tree_node_t *last = NULL;
    bt_node_queue_t *queue = NULL;

    if (!root ||
        !binaryTreeIsComplete(root, 0, binaryTreeSize(root)))
        return (NULL);

    queue = BTQueuePush(&queue, root);
    if (!queue)
        return (NULL);

    while (queue)
    {
        if ((queue->node->left &&
             !BTQueuePush(&queue, queue->node->left)) ||
            (queue->node->right &&
             !BTQueuePush(&queue, queue->node->right)))
        {
            BTQueueClear(&queue);
            return (NULL);
        }

        if (!queue->next)
        {
            if (queue->node->left)
                last = queue->node->left;
            else
                last = queue->node;
        }

        BTQueueAdvance(&queue);
    }

    return (last);
}
