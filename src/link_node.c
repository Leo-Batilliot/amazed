/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** link_node
*/

#include "my_printf.h"
#include "my_lists.h"
#include "my_strings.h"
#include "my_numbers.h"
#include "amaze.h"

static int add_link(list_t *node_one, list_t *node_two)
{
    if (node_one && node_two) {
        node_one->tab = my_realloc(node_one->tab,
            node_one->this_index * sizeof(list_t),
            (node_one->this_index + 1) * sizeof(list_t));
        if (!node_one->tab)
            return -1;
        node_one->tab[node_one->this_index] = node_two;
        node_one->this_index++;
        node_one->tab[node_one->this_index] = NULL;
        node_two->tab = my_realloc(node_two->tab,
            node_two->this_index * sizeof(list_t),
            (node_two->this_index + 1) * sizeof(list_t));
        if (!node_two->tab)
            return -1;
        node_two->tab[node_two->this_index] = node_one;
        node_two->this_index++;
        node_two->tab[node_two->this_index] = NULL;
    }
    return 0;
}

int link_node(char **new_array, list_t **head)
{
    list_t *node_one = find_node(*head, my_getnbr(new_array[0]));
    list_t *node_two = find_node(*head, my_getnbr(new_array[1]));

    if (!node_one || !node_two || (node_one->num == node_two->num))
        return 1;
    for (int i = 0; node_one->tab && node_one->tab[i]; i++) {
        if (node_one->tab[i] == node_two)
            return 1;
    }
    for (int i = 0; node_two->tab && node_two->tab[i]; i++) {
        if (node_two->tab[i] == node_one)
            return 1;
    }
    if (add_link(node_one, node_two) == -1)
        return -1;
    return 0;
}
