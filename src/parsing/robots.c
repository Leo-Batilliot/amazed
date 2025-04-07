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

static void move_file_content(linked_list_t **file_content)
{
    for (linked_list_t *tmp; *file_content &&
            ((char *)(*file_content)->data)[0] == '#'; free(tmp)) {
        tmp = *file_content;
        *file_content = (*file_content)->next;
    }
}

int get_robots_numbers(maze_t *maze, linked_list_t **file_content)
{
    char **content;

    move_file_content(file_content);
    content = split_string((*file_content)->data, " \t\n");
    if (content == NULL || content[0] == NULL ||
    my_array_len((void *)content) != 1) {
        return_and_free(maze, file_content, content);
        mini_printf(2, "Error: Robots number is invalid\n");
        return 1;
    }
    maze->nb_robots = my_getnbr(content[0]);
    if (maze->nb_robots < 1) {
        return_and_free(maze, file_content, content);
        mini_printf(2, "Error: Robots number is invalid\n");
        return 1;
    }
    my_free_word_array(content);
    mini_printf(1, "#number_of_robots\n%d\n", maze->nb_robots);
    return 0;
}
