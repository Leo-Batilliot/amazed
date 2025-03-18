/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** create node
*/

#include <unistd.h>

#include "lists.h"

/*
**  Creates a new node with the given data
*/
list_t *create_node(void *data)
{
    list_t *node = malloc(sizeof(list_t));

    if (!node) {
        write(2, "Error: node memory allocation failed\n", 37);
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}
