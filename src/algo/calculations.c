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

static path_t *get_shortest_path(linked_list_t *possible_paths)
{
    path_t *lowest = NULL;

    for (linked_list_t *tmp = possible_paths; tmp; tmp = tmp->next)
        if (!lowest || ((path_t *)tmp->data)->score < lowest->score)
            lowest = tmp->data;
    return lowest;
}

static int browse_neighbors(path_list_t *list, int *nb_paths, int opt)
{
    path_t *new_path = NULL;

    for (link_t *l = list->path->room->links_list; l; l = l->next_link) {
        if (l->room->visited || l->room == list->start || (opt &&
            !(list->path->prev) && l->room != list->end && l->room->robot))
            continue;
        new_path = init_path(l->room);
        if (!new_path)
            return 0;
        new_path->prev = list->path;
        new_path->score = list->path->score + 1;
        *(nb_paths) += 1 + add_to_end(&list->possible_paths, new_path);
    }
    return 0;
}

path_t *get_best_path(room_t *start, room_t *end, int opt)
{
    path_list_t list = {start, end, NULL, NULL};
    int nb_paths = 1;

    add_to_beggining(&list.possible_paths, init_path(start));
    for (int i = 0; nb_paths > 0; i++) {
        list.path = get_shortest_path(list.possible_paths);
        if (i && list.path->room == start) {
            free_path_list(&list.possible_paths);
            return NULL;
        }
        if (list.path->room == end) {
            list.path = path_copy(list.path);
            free_path_list(&list.possible_paths);
            return list.path;
        }
        nb_paths += (delete_nodes(&list.possible_paths, list.path) - 1);
        list.path->room->visited = browse_neighbors(&list, &nb_paths, opt) + 1;
    }
    free_path_list(&list.possible_paths);
    return NULL;
}

static void count_path_len(algo_t *algo)
{
    for (path_t *tmp = algo->path_wait; tmp; tmp = tmp->prev)
        algo->path_wait_cost++;
    for (path_t *tmp = algo->path; tmp; tmp = tmp->prev)
        algo->path_cost++;
}

static void get_room(algo_t *algo, path_t *head)
{
    for (path_t *tmp = head; tmp; tmp = tmp->prev)
        if (tmp->prev && !tmp->prev->prev)
            algo->room = tmp->room;
}

room_t *get_best_room(room_t *rooms_list, robot_t *robot, room_t *end)
{
    algo_t *algo = init_algo(rooms_list, robot, end);

    if (!algo)
        return NULL;
    count_path_len(algo);
    get_room(algo, algo->path_wait);
    if (algo->path_wait_cost <= 2 || !algo->room)
        return free_best_room(algo, end);
    if (algo->path_wait_cost + 1 + algo->room->waiting <
        algo->path_cost || !algo->path)
        return free_best_room(algo, NULL);
    get_room(algo, algo->path);
    return free_best_room(algo, NULL);
}
