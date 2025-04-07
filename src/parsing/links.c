/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** links
*/
#include "amazed.h"
#include "stddef.h"
#include "my_strings.h"
#include "stdlib.h"

static void add_to_link_list(link_t **begin, link_t *link)
{
    link_t *temp;

    if (!(*begin)) {
        *begin = link;
        return;
    }
    for (temp = *begin; temp->next_link; temp = temp->next_link);
    temp->next_link = link;
}

static int link_exists(room_t *first_room, room_t *second_room)
{
    for (link_t *temp = first_room->links_list; temp; temp = temp->next_link)
        if (temp->room == second_room)
            return 1;
    return 0;
}

static int init_links(link_t *l1, link_t *l2, room_t *r1, room_t *r2)
{
    if (!l1 && l2) {
        free(l2);
        return 1;
    }
    if (!l2 && l1) {
        free(l1);
        return 1;
    }
    if (!l2) {
        free(l1);
        free(l2);
        return 1;
    }
    l1->room = r1;
    l1->next_link = NULL;
    l2->room = r2;
    l2->next_link = NULL;
    return 0;
}

static void add_link_to_rooms(maze_t *maze, char *left, char *right)
{
    room_t *left_room = NULL;
    room_t *right_room = NULL;
    link_t *left_link = malloc(sizeof(link_t));
    link_t *right_link = malloc(sizeof(link_t));

    for (room_t *temp = maze->rooms_list; temp; temp = temp->next) {
        if (!my_strcmp(temp->room_name, left))
            left_room = temp;
        if (!my_strcmp(temp->room_name, right))
            right_room = temp;
    }
    if (init_links(left_link, right_link, right_room, left_room))
        return;
    mini_printf(1, "%s-%s\n", left, right);
    if (link_exists(left_room, right_room) || left_room == right_room)
        return;
    add_to_link_list(&left_room->links_list, left_link);
    add_to_link_list(&right_room->links_list, right_link);
}

static int check_room_valid(maze_t *maze, char **content)
{
    int nb = 0;

    for (room_t *temp = maze->rooms_list; temp && nb != 2; temp = temp->next) {
        if (!my_strcmp(temp->room_name, content[0]) ||
        !my_strcmp(temp->room_name, content[1]))
            nb++;
    }
    if (nb == 2 || (nb == 1 && !my_strcmp(content[0], content[1])))
        return 0;
    return 1;
}

int parse_link(maze_t *maze, char *line, int index)
{
    static int start = 1;
    char **array;

    remove_comment(line);
    array = split_string(line, "-");
    if (my_array_len((void *)array) != 2 || my_count_letter(line, '-') != 1)
        return mini_printf(2, "invalid line [l-%d]\n", index + 1);
    if (check_room_valid(maze, array))
        return mini_printf(2, "room(s) doesn't exist [l-%d]\n", index) + 1;
    if (start)
        start = mini_printf(1, "#tunnels\n");
    add_link_to_rooms(maze, array[0], array[1]);
    my_free_word_array(array);
    return 0;
}
