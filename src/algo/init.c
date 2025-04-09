/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>

path_t *path_copy(path_t *path)
{
    path_t *new = NULL;
    path_t *prev = NULL;
    path_t *head = NULL;

    for (path_t *current = path; current; current = current->prev) {
        new = malloc(sizeof(path_t));
        if (!new)
            return (NULL + free_path(head));
        new->room = current->room;
        new->score = current->score;
        new->prev = NULL;
        if (prev)
            prev->prev = new;
        else
            head = new;
        prev = new;
    }
    return head;
}

path_t *init_path(room_t *start)
{
    path_t *path = malloc(sizeof(path_t));

    if (!path)
        return NULL;
    path->room = start;
    path->score = 0;
    path->prev = NULL;
    return path;
}

algo_t *init_algo(room_t *rooms_list,
    robot_t *robot, room_t *end)
{
    algo_t *algo = malloc(sizeof(algo_t));

    algo->path_wait_cost = 0;
    algo->path_cost = 0;
    algo->room = NULL;
    for (room_t *tmp = rooms_list; tmp; tmp = tmp->next)
        tmp->visited = 0;
    algo->path_wait = get_best_path(robot->room, end, 0);
    for (room_t *tmp = rooms_list; tmp; tmp = tmp->next)
        tmp->visited = 0;
    algo->path = get_best_path(robot->room, end, 1);
    return algo;
}

robot_t *init_robots_list(room_t *start, int nb_robots)
{
    robot_t *robots = malloc(sizeof(robot_t));
    robot_t *tmp = robots;

    if (!robots)
        return NULL;
    robots->nbr = 1;
    robots->room = start;
    robots->prev = NULL;
    robots->next = NULL;
    for (int i = 1; i < nb_robots; i++) {
        tmp->next = malloc(sizeof(robot_t));
        if (!tmp->next)
            return NULL + (my_free(robots));
        tmp->next->prev = tmp;
        tmp = tmp->next;
        tmp->nbr = i + 1;
        tmp->room = start;
        tmp->next = NULL;
    }
    return robots;
}
