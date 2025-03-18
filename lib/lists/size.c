/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** size
*/

#include "lists.h"

/*
**  Returns the size of the list
*/
int list_size(list_t *list)
{
    int size = 0;

    while (list) {
        size++;
        list = list->next;
    }
    return size;
}
