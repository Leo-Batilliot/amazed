/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** lists
*/

#include "amazed.h"
#include "my_strings.h"
#include <stddef.h>
#include <stdlib.h>

static int compare_paths(path_t *p1, path_t *p2)
{
    if (p1->room == p2->room)
        return 1;
    return 0;
}

static linked_list_t *process_node(linked_list_t **list_ptr,
    linked_list_t *current, linked_list_t **prev, void *data)
{
    linked_list_t *next_node;
    linked_list_t *tmp;

    next_node = current->next;
    if (compare_paths((path_t *)current->data, (path_t *)data)) {
        tmp = current;
        if (!*prev)
            *list_ptr = next_node;
        else
        (*prev)->next = next_node;
        free(tmp);
    } else
        *prev = current;
    return next_node;
}

int delete_nodes(linked_list_t **list_ptr, void *data)
{
    linked_list_t *prev = NULL;

    if (!list_ptr || !(*list_ptr))
        return 0;
    for (linked_list_t *current = *list_ptr; current;
        current = process_node(list_ptr, current, &prev, data));
    return 0;
}

linked_list_t *my_find_node(linked_list_t *list, void *data)
{
    if (!list)
        return NULL;
    for (linked_list_t *tmp = list; tmp; tmp = tmp->next)
        if (compare_paths((path_t *)tmp->data, (path_t *)data))
            return tmp;
    return NULL;
}

int add_to_end(linked_list_t **list_ptr, void *data)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));
    linked_list_t *tmp = NULL;

    if (!new_node)
        return my_free(data);
    new_node->data = data;
    new_node->next = NULL;
    if (!*list_ptr) {
        *list_ptr = new_node;
        return 0;
    }
    for (tmp = *list_ptr; tmp->next; tmp = tmp->next);
    tmp->next = new_node;
    return 0;
}

int add_to_beggining(linked_list_t **list_ptr, void *data)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (!new_node)
        return my_free(data);
    new_node->data = data;
    new_node->next = *list_ptr;
    *list_ptr = new_node;
    return 0;
}

room_t *add_room_to_list(maze_t *maze, char *name, int posx, int posy)
{
    room_t *new_room = malloc(sizeof(room_t));
    room_t *tmp = NULL;

    new_room->room_name = my_strdup(name);
    new_room->posx = posx;
    new_room->posy = posy;
    new_room->robot = NULL;
    new_room->waiting = 0;
    new_room->visited = 0;
    new_room->links_list = NULL;
    new_room->next = NULL;
    new_room->prev = NULL;
    if (!maze->rooms_list) {
        maze->rooms_list = new_room;
        return new_room;
    }
    for (tmp = maze->rooms_list; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new_room;
    new_room->prev = tmp;
    return new_room;
}
