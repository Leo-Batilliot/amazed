/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** find node
*/

#include "my_lists.h"

/*
**  Finds a node in the list with the given reference
*/

list_t *find_node(list_t *head, int to_cmd)
{
    list_t *tmp = head;

    for (; tmp; tmp = tmp->next) {
        if (tmp->num == to_cmd) {
            return tmp;
        }
    }
    return NULL;
}
