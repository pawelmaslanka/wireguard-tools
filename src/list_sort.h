// SPDX-FileCopyrightText: 2023 Pawel Maslanka
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIST_SORT_H
#define LIST_SORT_H

//TASK_CHANGE: I added this file because it provides the implementation of an
// merge sort algorithm for the linked list.
// This fulfills the requirement no. 4 from the task.

#include <stddef.h>

/* The following 2 callbacks define operations on the internal link of list's node */
/**
 * Get a next node
 * @param source The node from which to get the next node
 * @return The next node, NULL if it was a last node in the list
 */
typedef void *(*list_node_get_next_cb)(void *source);

/**
 * Link together two nodes
 * @param source The node that is the parent of @next_node
 * @param next_node: The node that is referenced from @source
 */
typedef void (*list_node_set_next_cb)(void *source, void *next_node);

/**
 * Compare two nodes. It determines the order of the nodes in the list
 * @param first The node that is the parent of @next_node
 * @param second: The node that is referenced from @source
 * @return A negative value if the @first should be after the @second, 0 or positive otherwise
 */
typedef int (*list_node_compare_cb)(const void *first, const void *second);

/**
 * Sort a linked list using the merge sort algorithm
 * @param head Reference to the first node in the list
 * @param get_next A callback to get the next node
 * @param set_next A callback to link together two nodes
 * @param node_cmp A callback to compare two nodes to determine their expected order
 * @param node_size The size of the list's internal node
 * @return The head of a sorted list
 * @note Merge sort is a recursive algorithm. It does not use any dynamic memory allocation.
 *       For a very long list needs a deep stack.
 */
void *list_merge_sort(void *head,
    list_node_get_next_cb get_next, list_node_set_next_cb set_next,
    list_node_compare_cb node_cmp, size_t node_size);

#endif // LIST_SORT_H