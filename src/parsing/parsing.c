/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** parsing
*/
#include "amazed.h"
#include "my_strings.h"
#include "my_numbers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int check_line(maze_t *maze, char **line, int line_index, int found[2])
{
    if (my_array_len((void *)line) == 1 ||
        (my_array_len((void *)line) > 1 && line[1][0] == '#'))
        return parse_link(maze, line[0], line_index);
    else if (my_array_len((void *)line) == 3 ||
        (my_array_len((void *)line) > 3 && line[3][0] == '#'))
        return parse_room(maze, line, line_index, found);
    return mini_printf(2, "Invalid line [l-%d]\n", line_index) - 1;
}

static int comment_line(char **line, int found[2])
{
    if (!my_strcmp(line[0], "##start")) {
        found[0] = 1;
        return free_array((void **)line) + 1;
    }
    if (!my_strcmp(line[0], "##end")) {
        found[1] = 1;
        return free_array((void **)line) + 1;
    }
    if (line[0][0] == '#')
        return free_array((void **)line) + 1;
    return 0;
}

static int parsing_error(char **line, int line_index, int found[2])
{
    if (line == NULL || line[0] == NULL)
        return mini_printf(2, "NULL line [l-%d]\n", line_index) + 1;
    if (!my_strcmp(line[0], "##start") && found[0])
        return mini_printf(2, "double ##start [l-%d]\n", line_index) + 1;
    if (!my_strcmp(line[0], "##end") && found[1])
        return mini_printf(2, "double ##end [l-%d]\n", line_index) + 1;
    if ((!my_strcmp(line[0], "##end") && found[0]) ||
        (!my_strcmp(line[0], "##start") && found[1]))
        return mini_printf(2, "Start and end can't be the same room [l-%d]\n",
            line_index) + 1;
    return 0;
}

static maze_t *parse_maze(maze_t *maze,
    linked_list_t *file_content, int found[2], int line_index)
{
    char **line = NULL;

    for (linked_list_t *tmp = file_content->next; tmp; tmp = tmp->next) {
        line_index++;
        line = split_string(tmp->data, " \t\n");
        if (parsing_error(line, line_index, found))
            return free_lines(maze, &file_content, line);
        if (comment_line(line, found))
            continue;
        if (check_line(maze, line, line_index, found))
            return free_lines(maze, &file_content, line);
        found[0] = 0;
        found[1] = free_array((void **)line);
    }
    free_lists(&file_content);
    return maze;
}

maze_t *init_maze_and_parse(void)
{
    char *str = NULL;
    size_t size = 0;
    linked_list_t *file_content = NULL;
    maze_t *maze = malloc(sizeof(maze_t));
    int found[] = {0, 0};
    int line = 1;

    if (!maze)
        return NULL;
    maze->rooms_list = NULL;
    maze->start = NULL;
    maze->end = NULL;
    while (getline(&str, &size, stdin) != -1)
        add_to_end(&file_content, my_strdup(str));
    free(str);
    if (!file_content)
        return maze;
    if (get_robots_count(maze, &file_content, &line))
        return maze;
    return parse_maze(maze, file_content, found, line);
}
