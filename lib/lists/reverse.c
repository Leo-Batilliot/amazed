/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** reverse list
*/

#include "lists.h"

/*
**  Reverses the order of the list
*/
list_t *reverse_list(list_t *list)
{
    list_t *prev = NULL;
    list_t *next = NULL;

    while (list) {
        next = list->next;
        list->next = prev;
        prev = list;
        list = next;
    }
    return prev;
}
