// SPDX-FileCopyrightText: 2023 Pawel Maslanka
// SPDX-License-Identifier: GPL-3.0-or-later

//TASK_CHANGE: I added this file because it provides the implementation of an
// merge sort algorithm for the linked list.
// This fulfills the requirement no. 4 from the task.
#include "list_sort.h"

/**
 * Get the middle item of the list
 * @param head The first node of the list
 * @param get_next A callback to get the next node
 * @return The middle node
 * @note It is use only for internal purpose of merge sort algorithm
 */
static void *list_find_mid(void *head, list_node_get_next_cb get_next)
{
    void *single_jump = head; // Go through the list one by one
    void *double_jump = get_next(head); // Go through the list by every second node

    while (double_jump && get_next(double_jump)) {
        single_jump = get_next(single_jump);
        double_jump = get_next(get_next(double_jump)); 
    }

    return single_jump;
}

/**
 * Connect two nodes each together and move them to the next position
 * @param parent The node where @next should be connect to
 * @param next The node that should be connected to @parent
 * @param get_next A callback to get the next node
 * @param set_next A callback to link together two nodes
 * @note It is use only for internal purpose of merge sort algorithm.
 *       At the end, the @parent should refer to the @next, and the @next should refer to its successor
 */
inline static void list_node_link_and_move(
    void **parent, void **next,
    list_node_get_next_cb get_next, list_node_set_next_cb set_next)
{
    set_next(*parent, *next);
    *parent = *next;
    *next = get_next(*next);
}

/**
 * Merge two list in expected order
 * @param left The first list
 * @param right The second list
 * @param get_next A callback to get the next node
 * @param set_next A callback to link together two nodes
 * @param node_cmp A callback to compare two nodes to determine their expected order
 * @return The head node of merged and sorted list
 * @note It is use only for internal purpose of merge sort algorithm
 */
static void *list_merge(
    void *left, void *right,
    list_node_get_next_cb get_next, list_node_set_next_cb set_next,
    list_node_compare_cb node_cmp, void **result)
{
    if (!left)
        return right;
    
    if (!right)
        return left;

    // The 'result' keeps header of the list, the 'node' is used to link nodes one by one
    void *node = *result;
    // Merge two list
    while (left && right)
        if (node_cmp(&left, &right) < 0)
            list_node_link_and_move(&node, &left, get_next, set_next);
        else
            list_node_link_and_move(&node, &right, get_next, set_next);

    while (left)
        list_node_link_and_move(&node, &left, get_next, set_next);
    
    while (right)
        list_node_link_and_move(&node, &right, get_next, set_next);
    
    return get_next(*result);
}

void *list_merge_sort(void *head,
    list_node_get_next_cb get_next, list_node_set_next_cb set_next,
    list_node_compare_cb node_cmp, size_t node_size)
{
    // There must be at least 2 nodes to perform further action
    if (!head || !get_next(head))
        return head;
    
    // Find middle item to split the list into two halves
    void *mid = list_find_mid(head, get_next);
    void *left = head;
    void *right = get_next(mid);
    char result[node_size]; // The header of the sorted list
    void *sorted_list = &result; // To pass it for internal processing
    set_next(mid, NULL); // For the left half, the middle element is the last item
    
    // Recursive calls to decompose list into elementary nodes
    left = list_merge_sort(left, get_next, set_next, node_cmp, node_size);
    right = list_merge_sort(right, get_next, set_next, node_cmp, node_size);
    // Merge both left and right halves
    sorted_list = list_merge(left, right, get_next, set_next, node_cmp, (void**) &sorted_list);
    return sorted_list;
}