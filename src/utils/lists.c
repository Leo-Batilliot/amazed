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

linked_list_t *my_find_node(linked_list_t *list, void *data)
{
    if (!list)
        return NULL;
    for (linked_list_t *tmp = list; tmp; tmp = tmp->next)
        if (tmp->data == data)
            return tmp;
    return NULL;
}

void add_to_end(linked_list_t **list_ptr, void *data)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));
    linked_list_t *tmp;

    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = NULL;
    if (*list_ptr == NULL) {
        *list_ptr = new_node;
        return;
    }
    for (tmp = *list_ptr; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new_node;
}

void add_to_beggining(linked_list_t **list_ptr, void *data)
{
    linked_list_t *new_node = malloc(sizeof(linked_list_t));

    if (!new_node)
        return;
    new_node->data = data;
    new_node->next = *list_ptr;
    *list_ptr = new_node;
}

room_t *add_room_to_list(maze_t *maze, char *name, int posx, int posy)
{
    room_t *new_room = malloc(sizeof(room_t));
    room_t *tmp;

    new_room->room_name = my_strdup(name);
    new_room->posx = posx;
    new_room->posy = posy;
    new_room->robot = NULL;
    new_room->waiting = 0;
    new_room->visited = 0;
    new_room->links_list = NULL;
    new_room->next = NULL;
    new_room->prev = NULL;
    if (maze->rooms_list == NULL) {
        maze->rooms_list = new_room;
        return new_room;
    }
    for (tmp = maze->rooms_list; tmp->next != NULL; tmp = tmp->next);
    tmp->next = new_room;
    new_room->prev = tmp;
    return new_room;
}
