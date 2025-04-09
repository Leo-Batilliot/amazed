/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** count_letters
*/
#include "amazed.h"
#include "my_strings.h"

int cut_comment(char *str)
{
    int i = 0;

    if (!str)
        return 0;
    for (; str[i] && str[i] != '#'; i++);
    if (str[i] == '#')
        str[i] = '\0';
    return 0;
}

int count_letter(char *str, char letter)
{
    int count = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == letter)
            count++;
    return count;
}

maze_t *free_lines(maze_t *maze, linked_list_t **file_lines, char **array)
{
    free_lists(file_lines);
    free_array((void **)array);
    return maze;
}
