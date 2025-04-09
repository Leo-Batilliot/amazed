/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_list
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>

int free_lists(linked_list_t **list_ptr)
{
    linked_list_t *tmp;

    if (!list_ptr || !(*list_ptr))
        return 0;
    while (*list_ptr) {
        tmp = *list_ptr;
        *list_ptr = (*list_ptr)->next;
        free(tmp->data);
        free(tmp);
    }
    *list_ptr = NULL;
    return 0;
}
