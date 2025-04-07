/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** calculations
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

static int get_distance(room_t *start, room_t *end)
{
    int distance = 1;

    if (start == end)
        return 0;
    for (link_t *l = start->links_list; l; l = l->next_link) {
        if (l->room == end)
            return distance;
        distance++;
    }
    return -1;
}

static path_t *get_shortest_path(linked_list_t *possible_paths)
{
    path_t *lowest = NULL;

    for (linked_list_t *tmp = possible_paths; tmp; tmp = tmp->next)
        if (!lowest || ((path_t *)tmp->data)->score < lowest->score)
            lowest = tmp->data;
    return lowest;
}

static void browse_neighbors(path_list_t *list, int *nb_paths, int opt)
{
    path_t *new_path = NULL;
    int cost = 0;

    for (link_t *l = list->path->room->links_list; l; l = l->next_link) {
        if (l->room->visited || l->room == list->start
        || (opt && !(list->path->prev) &&
        l->room != list->end && l->room->robot))
            continue;
        new_path = init_path(l->room);
        if (!new_path)
            return;
        new_path->prev = list->path;
        new_path->score = list->path->score + 1;
        cost = get_distance(l->room, list->end);
        new_path->distance = (cost == -1) ? new_path->score : INT_MIN + cost;
        if (!my_find_node(list->possible_paths, new_path)) {
            *(nb_paths) += 1;
            add_to_end(&list->possible_paths, new_path);
        }
    }
}

static void add_data_to_path(
    path_t *path, room_t *room, int distance, int score)
{
    path->room = room;
    path->distance = distance;
    path->score = score;
    path->prev = NULL;
}

static path_t *path_copy(path_t *path)
{
    path_t *new = NULL;
    path_t *prev = NULL;
    path_t *head = NULL;

    for (path_t *current = path; current; current = current->prev) {
        new = malloc(sizeof(path_t));
        if (!new) {
            free_path(head);
            return NULL;
        }
        add_data_to_path(new, current->room,
            current->distance, current->score);
        if (prev)
            prev->prev = new;
        else
            head = new;
        prev = new;
    }
    return head;
}

path_t *get_best_path(room_t *start, room_t *end, int opt)
{
    path_list_t list = {start, end, NULL, NULL};
    int nb_paths = 1;

    add_to_beggining(&list.possible_paths, init_path(start));
    for (int i = 0; nb_paths > 0; i++) {
        list.path = get_shortest_path(list.possible_paths);
        if (i && list.path->room == start)
            return NULL;
        if (list.path->room == end) {
            list.path = path_copy(list.path);
            free_path_list(list.possible_paths);
            return list.path;
        }
        nb_paths--;
        my_delete_nodes(&list.possible_paths, list.path);
        list.path->room->visited = 1;
        browse_neighbors(&list, &nb_paths, opt);
    }
    free_path_list(list.possible_paths);
    return NULL;
}

static algo_t *init_robot_path(room_t *rooms_list,
    robot_t *robot, room_t *end)
{
    algo_t *robot_path = malloc(sizeof(algo_t));

    robot_path->path_wait_cost = 0;
    robot_path->path_cost = 0;
    robot_path->room = NULL;
    for (room_t *tmp = rooms_list; tmp; tmp = tmp->next)
        tmp->visited = 0;
    robot_path->path_wait = get_best_path(robot->room, end, 0);
    for (room_t *tmp = rooms_list; tmp; tmp = tmp->next)
        tmp->visited = 0;
    robot_path->path = get_best_path(robot->room, end, 1);
    return robot_path;
}

room_t *get_best_room(room_t *rooms_list, robot_t *robot, room_t *end)
{
    algo_t *robot_path = init_robot_path(rooms_list, robot, end);

    if (!robot_path)
        return NULL;
    for (path_t *tmp = robot_path->path_wait; tmp; tmp = tmp->prev) {
        robot_path->path_wait_cost++;
        if (tmp->prev && !tmp->prev->prev)
            robot_path->room = tmp->room;
    }
    if (robot_path->path_wait_cost <= 2 || !robot_path->room)
        return free_best_room(robot_path, end);
    for (path_t *tmp = robot_path->path; tmp; tmp = tmp->prev)
        robot_path->path_cost++;
    if (robot_path->path_wait_cost + 1 + robot_path->room->waiting <
        robot_path->path_cost || !robot_path->path)
        return free_best_room(robot_path, NULL);
    for (path_t *tmp = robot_path->path; tmp; tmp = tmp->prev)
        if (tmp->prev && !tmp->prev->prev)
            robot_path->room = tmp->room;
    return free_best_room(robot_path, NULL);
}
