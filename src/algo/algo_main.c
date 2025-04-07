/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** algo
*/
#include "amazed.h"
#include "stddef.h"

static void display_moves(maze_t *maze, room_t *room, robot_t *tmp, int *start)
{
    if (room->robot != NULL && maze->end != room && tmp->room == maze->start)
        return;
    if (*start == 0)
        mini_printf(1, " ");
    *start = 0;
    mini_printf(1, "P%d-%s", tmp->nbr, (tmp->room)->room_name);
}

static void move_robots(maze_t *maze)
{
    int start = 1;
    room_t *room = NULL;

    for (room_t *temp = maze->rooms_list; temp; temp = temp->next) {
        temp->robot = NULL;
        temp->waiting = 0;
    }
    for (robot_t *robot = maze->robots_list; robot; robot = robot->next) {
        room = get_best_room(maze->rooms_list, robot, maze->end);
        if (room->robot && room != maze->end)
            room->waiting++;
        else {
            robot->room = room;
            room->robot = robot;
        }
        display_moves(maze, room, robot, &start);
    }
    mini_printf(1, "\n");
}

int algo_main(maze_t *maze)
{
    mini_printf(1, "#moves\n");
    while (maze->robots_list) {
        move_robots(maze);
        free_end_robots(maze->end, &maze->robots_list);
    }
    return 0;
}
