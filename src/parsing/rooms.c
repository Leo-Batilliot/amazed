/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** rooms
*/
#include "amazed.h"
#include "my_numbers.h"
#include "my_strings.h"

static int display_room(maze_t *maze, room_t *room, int found[2])
{
    if (found[0]) {
        maze->start = room;
        mini_printf(1, "##start\n");
    }
    if (found[1]) {
        maze->end = room;
        mini_printf(1, "##end\n");
    }
    return mini_printf(1, "%s %d %d\n",
        room->room_name, room->posx, room->posy);
}

int parse_room(maze_t *maze, char **line, int index, int found[2])
{
    static int first_time = 1;
    int posx = my_getnbr(line[1]);
    int posy = 0;

    if (!my_str_isnum(line[1]) || !my_str_isnum(line[2]))
        return mini_printf(2,
            "Room position has to be numerical [l-%d]\n", index) + 1;
    posy = cut_comment(line[2]) + my_getnbr(line[2]);
    for (room_t *tmp = maze->rooms_list; tmp; tmp = tmp->next)
        if (!my_strcmp(tmp->room_name, line[0]) ||
        (tmp->posx == posx && tmp->posy == posy))
            return mini_printf(2,
                "Room name/position already used [l-%d]\n", index) + 1;
    if (first_time)
        first_time = mini_printf(1, "#rooms\n");
    return display_room(maze,
        add_room_to_list(maze, line[0], posx, posy), found);
}
