/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>

path_t *init_path(room_t *start)
{
    path_t *path = malloc(sizeof(path_t));

    path->room = start;
    path->distance = 0;
    path->score = 0;
    path->prev = NULL;
    return path;
}

robot_t *init_robots_list(room_t *start, int nb_robots)
{
    robot_t *robots = malloc(sizeof(robot_t));
    robot_t *tmp = robots;

    robots->nbr = 1;
    robots->room = start;
    robots->prev = NULL;
    robots->next = NULL;
    for (int i = 1; i < nb_robots; i++) {
        tmp->next = malloc(sizeof(robot_t));
        tmp->next->prev = tmp;
        tmp = tmp->next;
        tmp->nbr = i + 1;
        tmp->room = start;
        tmp->next = NULL;
    }
    return robots;
}
