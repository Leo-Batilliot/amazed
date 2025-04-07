/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>

static void free_robots_list(robot_t *robot)
{
    for (robot_t *next = NULL; robot; robot = next) {
        next = robot->next;
        free(robot);
    }
}

static void free_links_list(link_t *link)
{
    for (link_t *next = NULL; link; link = next) {
        next = link->next_link;
        free(link);
    }
}

static void free_rooms_list(room_t *room)
{
    for (room_t *next = NULL; room; room = next) {
        next = room->next;
        if (room->links_list)
            free_links_list(room->links_list);
        if (room->room_name)
            free(room->room_name);
        free(room);
    }
}

int free_maze(maze_t *maze)
{
    if (!maze)
        return 0;
    if (maze->robots_list)
        free_robots_list(maze->robots_list);
    if (maze->rooms_list)
        free_rooms_list(maze->rooms_list);
    free(maze);
    return 0;
}

void free_path_list(linked_list_t *list)
{
    for (linked_list_t *next = NULL; list; list = next) {
        next = list->next;
        free(list);
    }
}

void free_path(path_t *path)
{
    for (path_t *temp = NULL; path; path = temp) {
        temp = path->prev;
        path->prev = NULL;
        free(path);
    }
}

room_t *free_best_room(algo_t *path, room_t *room)
{
    room_t *res;

    if (!path)
        return room ? room : NULL;
    res = room ? room : path->room;
    if (path->path)
        free_path(path->path);
    if (path->path_wait)
        free_path(path->path_wait);
    free(path);
    return res;
}

void free_end_robots(room_t *end, robot_t **robots)
{
    robot_t *next = NULL;

    if (!robots || !(*robots))
        return;
    for (robot_t *tmp = *robots; tmp; tmp = next) {
        next = tmp->next;
        if (tmp->room != end)
            continue;
        if (!tmp->prev)
            *robots = tmp->next;
        if (!tmp->prev && tmp->next)
            tmp->next->prev = NULL;
        if (tmp->prev)
            tmp->prev->next = tmp->next;
        if (tmp->prev && tmp->next)
            tmp->next->prev = tmp->prev;
        free(tmp);
    }
}
