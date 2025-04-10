/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** parsing
*/

#include "../include/bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>

static int check_word(char *line, int *is_room,
    int *is_link, main_struct_t *main_struct, int *is_move)
{
    if (!strcmp("#rooms", line)) {
        *is_room = 1;
        return 1;
    }
    if (!strcmp("#tunnels", line)) {
        *is_room = 0;
        *is_link = 1;
        return 1;
    }
    if (!strcmp("#moves", line)) {
        *is_link = 0;
        get_min_max(main_struct);
        create_list_robot(main_struct);
        *is_move = 1;
        return 1;
    }
    return 0;
}

static int update_rooms(int *_end, int *_start, char *line, main_struct_t *main_struct, int is_room)
{
    char **array = NULL;

    if (is_room == 1) {
        array = split_string(line, " \t");
        if (!strcmp("##start", line)) {
            *_start = 1;
            return 1;
        }
        if (!strcmp("##end", line)) {
            *_end = 1;
            return 1;
        }
        add_to_node(main_struct, *_start, *_end, array);
        *_end = 0;
        *_start = 0;
    }
    return 0;
}

static int update_links(char *line, main_struct_t *main_struct, int is_link)
{
    char **array = NULL;

    if (is_link == 1) {
        array = split_string(line, "-");
        add_to_link(array, main_struct);
    }
    return 0;
}

int parse_robot_position(char **split, main_struct_t *main_struct, robot_t *tmp, int *found)
{
    char *to_cmp = NULL;
    sfVector2f pos = {0, 0};

    for (int i = 0; split[i]; i++) {
        if (split[i][0] == 'P') {
            to_cmp = split[i] + 1;
            if (!strcmp(to_cmp, tmp->id)) {
                pos = ret_pos(split[i + 1], main_struct);
                add_pos_to_robot(tmp, pos);
                tmp->last_pos = pos;
                *found = 1;
                break;
            }
        }
    }
    if (*found == 0)
        add_pos_to_robot(tmp, tmp->last_pos);
    return 0;
}

int update_move(int is_move, char *line, main_struct_t *main_struct)
{
    int found = 0;
    char **split = NULL;

    if (is_move == 1) {
        split = split_string(line, " -\t");
        for (robot_t *tmp = main_struct->robot; tmp; tmp = tmp->next) {
            found = 0;     
            parse_robot_position(split, main_struct, tmp, &found);      
        }
        main_struct->nb_tour++;
    }
    return 0;
}

int parsing_file(FILE *fd, main_struct_t *main_struct)
{
    int is_room = 0;
    int is_link = 0;
    int is_move = 0;
    int count = 0;
    size_t size = 0;
    char *line = NULL;
    int _start = 0;
    int _end = 0;

    while (getline(&line, &size, fd) != -1) {
        line[strlen(line) - 1] = '\0';
        if (count == 0)
            main_struct->nb_robots = strdup(line);
        if (check_word(line, &is_room, &is_link, main_struct, &is_move) == 1)
            continue;
        if (update_rooms(&_end, &_start, line, main_struct, is_room) == 1)
            continue;
        update_links(line, main_struct, is_link);
        update_move(is_move, line, main_struct);
        count++;
    }
    return 0;
}
