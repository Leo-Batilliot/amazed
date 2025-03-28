/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** create node
*/

#include <unistd.h>

#include "my_lists.h"
#include "my_strings.h"
#include "my_numbers.h"

/*
**  Creates a new node with the given data
*/
list_t *create_node(char **array, int is_start, int is_end)
{
    list_t *node = malloc(sizeof(list_t));

    if (!node) {
        write(2, "Error: node memory allocation failed\n", 37);
        return NULL;
    }
    node->tab = NULL;
    node->is_end = is_end;
    node->is_start = is_start;
    node->num = my_getnbr(array[0]);
    node->index[0] = my_getnbr(array[1]);
    node->index[1] = my_getnbr(array[2]);
    node->this_index = 0;
    node->tab = malloc(sizeof(list_t *) * 10000);
    node->next = NULL;
    return node;
}
