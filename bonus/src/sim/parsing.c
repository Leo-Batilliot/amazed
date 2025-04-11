/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** parsing
*/

#include "bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>

static int check_word(char *line, int *type, sim_t *sim)
{
    if (!strcmp("#rooms", line)) {
        *type = 1;
        return 1;
    }
    if (!strcmp("#tunnels", line)) {
        get_min_max(sim);
        create_list_robot(sim);
        *type = 2;
        return 1;
    }
    if (!strcmp("#moves", line)) {
        *type = 3;
        return 1;
    }
    return 0;
}

static int update_rooms(int start_end[2], char *line, sim_t *sim)
{
    char **array = split_string(line, " \t");

    if (!array)
        return 1;
    if (!strcmp("##start", line)) {
        start_end[0] = 1;
        return free_array((void **)array) + 1;
    }
    if (!strcmp("##end", line)) {
        start_end[1] = 1;
        return free_array((void **)array) + 1;
    }
    add_to_node(sim, start_end, array);
    start_end[0] = 0;
    start_end[1] = 0;
    return free_array((void **)array);
}

static int set_array(link_t *node, sim_t *sim)
{
    node->array = sfVertexArray_create();
    if (!node->array)
        return 1;
    sfVertexArray_setPrimitiveType(node->array, sfLines);
    sfVertex p1 = {.position = get_pos(node->link_a, sim), .color = sfWhite};
    sfVertex p2 = {.position = get_pos(node->link_b, sim), .color = sfWhite};
    sfVertexArray_append(node->array, p1);
    sfVertexArray_append(node->array, p2);
    return 0;
}

static int update_links(char *line, sim_t *sim)
{
    char **array = split_string(line, "-");
    link_t *node;

    if (!array)
        return 1;
    node = malloc(sizeof(link_t));
    if (!node)
        return free_array((void **)array) + 1;
    node->link_a = strdup(array[0]);
    node->link_b = strdup(array[1]);
    if (set_array(node, sim))
        return free_array((void **)array) + 1;
    node->next = sim->link;
    sim->link = node;
    return free_array((void **)array) + 1;
}

sfVector2f get_pos(char *to_find, sim_t *sim)
{
    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next)
        if (!strcmp(tmp->name_room, to_find))
            return tmp->pos;
    return (sfVector2f){0, 0};
}

int parse_robot_position(char **split, sim_t *sim, robot_t *tmp)
{
    char *to_cmp = NULL;
    sfVector2f pos = {0, 0};

    for (int i = 0; split[i]; i++) {
        if (split[i][0] != 'P')
            continue;
        to_cmp = split[i] + 1;
        if (!strcmp(to_cmp, tmp->id)) {
            pos = get_pos(split[i + 1], sim);
            add_pos_to_robot(tmp, pos);
            tmp->last_pos = pos;
            return 0;
        }
    }
    add_pos_to_robot(tmp, tmp->last_pos);
    return 0;
}

int update_move(char *line, sim_t *sim)
{
    char **split = split_string(line, " -\t");

    if (!split)
        return 1;
    for (robot_t *tmp = sim->robot; tmp; tmp = tmp->next)
        parse_robot_position(split, sim, tmp);
    sim->nb_tour++;
    free_array((void **)split);
    return 0;
}

static int parse_line(int type, char *line, sim_t *sim, int start_end[2])
{
    if (type == 1)
        return update_rooms(start_end, line, sim);
    if (type == 2)
        return update_links(line, sim);
    if (type == 3)
        return update_move(line, sim);
    return 0;
}

int parse_file(FILE *fd, sim_t *sim)
{
    int type = -1;
    size_t size = 0;
    char *line = NULL;
    int start_end[2] = {0, 0};

    for (int i = 0; getline(&line, &size, fd) != -1; i++) {
        if (!line)
            continue;
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';
        if (i == 1)
            sim->nb_robots = strdup(line);
        if (check_word(line, &type, sim))
            continue;
        parse_line(type, line, sim, start_end);
    }
    free(line);
    return 0;
}
