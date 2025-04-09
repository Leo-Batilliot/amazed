/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** robots
*/
#include "amazed.h"
#include "my_numbers.h"
#include "my_strings.h"
#include <stddef.h>
#include <stdlib.h>

static void skip_comments(linked_list_t **lines, int *line_nb)
{
    for (linked_list_t *tmp; *lines && ((char *)(*lines)->data)[0] == '#';
        *line_nb += 1 + my_free((void *)tmp->data) + my_free((void *)tmp)) {
        tmp = *lines;
        *lines = (*lines)->next;
    }
}

int get_robots_count(maze_t *maze, linked_list_t **lines, int *line_nb)
{
    char **array = NULL;

    skip_comments(lines, line_nb);
    array = split_string((*lines)->data, " \t\n");
    if (!array || !array[0] || my_array_len((void *)array) != 1 ||
        !my_str_isnum(array[0]))
        return mini_printf(2, "Invalid robots count [l-%d]\n", *line_nb) + 1 +
            free_array((void **)array) + free_lists(lines);
    maze->nb_robots = my_getnbr(array[0]);
    if (maze->nb_robots <= 0)
        return mini_printf(2, "Robots count must be positive [l-%d]\n",
            *line_nb) + 1 + free_array((void **)array) + free_lists(lines);
    return mini_printf(1, "#number_of_robots\n%d\n", maze->nb_robots) +
        free_array((void **)array);
}
