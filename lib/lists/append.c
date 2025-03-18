/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** append
*/

#include "lists.h"

/*
** Appends a node to the end of the list
*/
void append_node(list_t **list, void *data)
{
    list_t *node = create_node(data);
    list_t *tmp = *list;

    if (node == NULL)
        return;
    if (*list == NULL) {
        *list = node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}
