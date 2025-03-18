/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** add to top
*/

#include "lists.h"

/*
** Adds a node to the top of the list
*/
void add_to_top(list_t **list, void *data)
{
    list_t *node = malloc(sizeof(list_t));

    if (!node)
        return;
    node->data = data;
    node->next = *list;
    *list = node;
}
