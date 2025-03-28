/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** append
*/

#include "my_lists.h"

/*
** Appends a node to the end of the list
*/
void append_node(list_t **list, char **array, int is_start, int is_end)
{
    list_t *node = create_node(array, is_start, is_end);
    list_t *tmp = *list;

    if (node == NULL)
        return;
    if (*list == NULL) {
        *list = node;
        return;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
}
