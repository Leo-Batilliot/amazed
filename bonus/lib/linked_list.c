/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** linked_list
*/

#include "bonus.h"
#include <stdlib.h>
#include <stdio.h>


int add_to_node(sim_t *sim, int start_end[2], char **array)
{
    rooms_t *node = malloc(sizeof(rooms_t));

    if (!node)
        return -1;
    node->start_end = start_end[0] + start_end[1] * 2;
    node->name_room = strdup(array[0]);
    node->pos = (sfVector2f){atoi(array[1]), atoi(array[2])};
    node->next = sim->list;
    sim->list = node;
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
    if (!robot->positions) {
        robot->positions = node;
        return 0;
    }
    tmp = robot->positions;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
    return 0;
}
