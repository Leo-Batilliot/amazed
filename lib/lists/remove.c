/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** remove node
*/

#include "lists.h"

/*
** void (*free_data)(void *data) is a function pointer
** that will be used to free the data of the node
**
** It's up to you to implement this function
*/

/*
** Removes the node with the given data
** using the function pointer passed as parameter
*/
void remove_node(list_t **list, void const *data, void (*free_data)(void *),
    int (*cmp)(void const *data, void const *ref))
{
    list_t *tmp = *list;
    list_t *prev = NULL;

    if (tmp == NULL)
        return;
    if (cmp(tmp->data, data) == 0) {
        *list = tmp->next;
        free_data(tmp->data);
        free(tmp);
        return;
    }
    while (tmp && cmp(tmp->data, data) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free_data(tmp->data);
    free(tmp);
}
