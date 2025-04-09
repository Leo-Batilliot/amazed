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

static void add_link(link_t **begin, link_t *link)
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

static int init_links(link_t **l1, link_t **l2, room_t *r1, room_t *r2)
{
    *l1 = malloc(sizeof(link_t));
    if (!(*l1))
        return 1;
    *l2 = malloc(sizeof(link_t));
    if (!(*l2))
        return my_free(*l1) + 1;
    (*l1)->room = r1;
    (*l1)->next_link = NULL;
    (*l2)->room = r2;
    (*l2)->next_link = NULL;
    return 0;
}

static void create_links(maze_t *maze, char *left, char *right)
{
    room_t *lroom = NULL;
    room_t *rroom = NULL;
    link_t *llink = NULL;
    link_t *rlink = NULL;

    for (room_t *temp = maze->rooms_list; temp; temp = temp->next) {
        if (!my_strcmp(temp->room_name, left))
            lroom = temp;
        if (!my_strcmp(temp->room_name, right))
            rroom = temp;
    }
    if (init_links(&llink, &rlink, rroom, lroom))
        return;
    mini_printf(1, "%s-%s\n", left, right);
    if (link_exists(lroom, rroom) || lroom == rroom)
        return (void) (my_free(llink) + my_free(rlink));
    add_link(&lroom->links_list, llink);
    add_link(&rroom->links_list, rlink);
}

static int room_doesnt_exist(maze_t *maze, char **array)
{
    int nb = 0;

    for (room_t *temp = maze->rooms_list; temp && nb != 2; temp = temp->next) {
        if (!my_strcmp(temp->room_name, array[0]))
            nb++;
        if (!my_strcmp(temp->room_name, array[1]))
            nb++;
    }
    return nb == 2 ? 0 : 1;
}

int parse_link(maze_t *maze, char *line, int index)
{
    static int start = 1;
    char **array = NULL + cut_comment(line);

    array = split_string(line, "-");
    if (my_array_len((void **)array) != 2 || count_letter(line, '-') != 1)
        return mini_printf(2, "invalid line [l-%d]\n", index) +
            free_array((void **)array) - 1;
    if (room_doesnt_exist(maze, array))
        return mini_printf(2, "invalid room(s) name(s) [l-%d]\n", index) +
            free_array((void **)array) + 1;
    if (start)
        start = mini_printf(1, "#tunnels\n");
    create_links(maze, array[0], array[1]);
    return free_array((void **)array);
}
