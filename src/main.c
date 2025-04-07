/*
** EPITECH PROJECT, 2024
** c_proj_template
** File description:
** main
*/
#include "amazed.h"
#include <stdlib.h>
#include <stddef.h>
#include "my_strings.h"

static int maze_error_handling(maze_t *maze)
{
    path_t *path = NULL;

    if (!maze)
        return 1;
    if (maze->return_value == 84)
        return 1;
    if (!maze->start || !maze->end)
        return mini_printf(2, "No start/end room\n") + 1;
    for (room_t *tmp = maze->rooms_list; tmp; tmp = tmp->next) {
        if (tmp->links_list)
            break;
        if (!tmp->next)
            return mini_printf(2, "No links found\n") + 1;
    }
    if (!maze->start->links_list || !maze->end->links_list)
        return mini_printf(2, "Maze can't be solved\n") + 1;
    path = get_best_path(maze->start, maze->end, 0);
    if (!path)
        return mini_printf(2, "Maze can't be solved\n") + 1;
    free_path(path);
    return 0;
}

int main(int ac, char **av)
{
    maze_t *maze;
    int res = 0;

    (void) av;
    if (ac != 1)
        return 84;
    maze = init_maze_and_parse();
    if (maze_error_handling(maze))
        return free_maze(maze) + 84;
    maze->robots_list = init_robots_list(maze->start, maze->nb_robots);
    if (!maze->robots_list || maze->return_value == 84)
        res = 84;
    else
        algo_main(maze);
    return res + free_maze(maze);
}
