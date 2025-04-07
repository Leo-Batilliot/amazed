/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** count_letters
*/
#include "amazed.h"
#include "my_strings.h"

void remove_comment(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] && str[i] != '#')
        i++;
    if (str[i] == '#')
        str[i] = '\0';
}

int my_count_letter(char *str, char c)
{
    int count = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            count++;
    return count;
}

int my_array_len(void **array)
{
    int res = 0;

    for (; array && array[res]; res++);
    return res;
}

void *return_and_free(maze_t *maze, linked_list_t **file_content, char **line)
{
    my_free_list(file_content);
    maze->return_value = 84;
    my_free_word_array(line);
    return maze;
}
