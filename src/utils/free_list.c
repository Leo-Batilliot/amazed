/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_list
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>

void my_free_list(linked_list_t **list_ptr)
{
    linked_list_t *tmp;

    if (!list_ptr || !(*list_ptr))
        return;
    while (*list_ptr) {
        tmp = *list_ptr;
        *list_ptr = (*list_ptr)->next;
        free(tmp->data);
        free(tmp);
    }
    *list_ptr = NULL;
}

static linked_list_t *process_node(linked_list_t **list_ptr,
    linked_list_t *current, linked_list_t **prev, void *data)
{
    linked_list_t *next_node;
    linked_list_t *tmp;

    next_node = current->next;
    if (current->data == data) {
        tmp = current;
        if (*prev == NULL)
            *list_ptr = next_node;
        else
        (*prev)->next = next_node;
        free(tmp);
    } else {
        *prev = current;
    }
    return next_node;
}

void my_delete_nodes(linked_list_t **list_ptr, void *data)
{
    linked_list_t *prev = NULL;
    linked_list_t *current = NULL;

    if (!list_ptr || !(*list_ptr))
        return;
    current = *list_ptr;
    while (current)
        current = process_node(list_ptr, current, &prev, data);
}
