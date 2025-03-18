/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** sort
*/

#include "lists.h"

/*
** Merge two sorted lists
** How it works: Compare the first element of each list,
** add the smallest to the result list
** and call the function again with the next element of the list
** that had the smallest element
*/
list_t *sorted_merge(list_t *a, list_t *b,
    int (*cmp)(void const *data1, void const *data2))
{
    list_t *result = NULL;

    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (cmp(a->data, b->data) <= 0) {
        result = a;
        result->next = sorted_merge(a->next, b, cmp);
    } else {
        result = b;
        result->next = sorted_merge(a, b->next, cmp);
    }
    return result;
}

/*
**  Split the list in two parts
**  How it works: slow pointer moves one step at a time,
**  fast pointer moves two steps at a time
*/
void split(list_t *src, list_t **front, list_t **back)
{
    list_t *slow = src;
    list_t *fast = src->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = src;
    *back = slow->next;
    slow->next = NULL;
}

/*
** Merge sort algorithm
** How it works: split the list in two parts,
** sort each part and merge them back together
*/
void merge_sort(list_t **list,
    int (*cmp)(void const *data1, void const *data2))
{
    list_t *head = *list;
    list_t *a;
    list_t *b;

    if (head == NULL || head->next == NULL)
        return;
    split(head, &a, &b);
    merge_sort(&a, cmp);
    merge_sort(&b, cmp);
    *list = sorted_merge(a, b, cmp);
}
