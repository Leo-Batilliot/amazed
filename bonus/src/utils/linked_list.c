/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** linked_list
*/

#include "../../include/bonus.h"
#include <stdlib.h>
#include <stdio.h>

int add_to_link(char **array, main_struct_t *main_struct)
{
    link_t *node = malloc(sizeof(link_t));

    if (!node)
        return -1;
    node->link_a = array[0];
    node->link_b = array[1];
    node->next = main_struct->link;
    main_struct->link = node;
    return 0;
}

int add_to_node(main_struct_t *main_struct, int _start, int _end, char **array)
{
    rooms_t *node = malloc(sizeof(rooms_t));

    if (!node)
        return -1;
    node->is_end = _end;
    node->is_start = _start;
    node->name_room = array[0];
    if (!node->name_room)
        return -1;
    node->pos = (sfVector2f){atoi(array[1]), atoi(array[2])};
    node->next = main_struct->list;
    main_struct->list = node;
    return 0;
}

int add_pos_to_robot(robot_t *robot, sfVector2f pos)
{
    round_t *node = malloc(sizeof(round_t));
    round_t *tmp = NULL;

    if (!node)
        return -1;
    node->pos = pos;
    node->next = NULL;
    if (!robot->robots) {
        robot->robots = node;
    } else {
        tmp = robot->robots;
        for (; tmp->next; tmp = tmp->next);
        tmp->next = node;
    }
    return 0;
}
