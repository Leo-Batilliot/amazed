/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** print
*/

#include "bonus.h"

static sfVector2f get_end_room(sim_t *sim)
{
    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next)
        if (tmp->start_end == 2)
            return tmp->pos;
    return (sfVector2f){0, 0};
}

static sfVector2f get_start_room(sim_t *sim)
{
    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next)
        if (tmp->start_end == 1)
            return tmp->pos;
    return (sfVector2f){0, 0};
}

void print_rooms(sim_t *sim, sfText *text, sfRenderWindow *window)
{
    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next) {
        sfVector2u size = sfTexture_getSize(sim->room_text);
        sfSprite_setOrigin(sim->room_sprite, (sfVector2f){size.x / 5.0f, size.y});
        sfSprite_setPosition(sim->room_sprite, tmp->pos);
        sfRenderWindow_drawSprite(window, sim->room_sprite, NULL);
        sfText_setString(text, tmp->name_room);
        sfText_setPosition(text, (sfVector2f){tmp->pos.x + 15, tmp->pos.y});
        sfText_setColor(sim->str_rooms, sfWhite);
        if (tmp->start_end == 2)
            sfText_setColor(text, sfRed);
        if (tmp->start_end == 1)
            sfText_setColor(text, sfGreen);
        sfRenderWindow_drawText(window, text, NULL);
    }
}

void print_lines(sim_t *sim, sfRenderWindow *window)
{
    for (link_t *tmp = sim->link; tmp; tmp = tmp->next)
        sfRenderWindow_drawVertexArray(window, tmp->array, NULL);
}

void draw_all(sim_t *sim, sfRenderWindow *window)
{
    sfVector2f end_room = get_end_room(sim);
    sfVector2f start_room = get_start_room(sim);
    sfBool first = sfTrue;
    int arrived = 0;
    char *arrived_str = NULL;

    sfRenderWindow_clear(window, sfBlack);
    print_lines(sim, window);
    for (robot_t *cur = sim->robot; cur; cur = cur->next) {
        if (sfSprite_getPosition(cur->robot_sprite).x == end_room.x &&
            sfSprite_getPosition(cur->robot_sprite).y == end_room.y) {
            arrived++;
            continue;
        }
        if (sfSprite_getPosition(cur->robot_sprite).x != start_room.x &&
            sfSprite_getPosition(cur->robot_sprite).y != start_room.y) {
            sfRenderWindow_drawText(window, cur->text, NULL);
                sfRenderWindow_drawSprite(window, cur->robot_sprite, NULL);
        } else if (first) {
            sfRenderWindow_drawSprite(window, cur->robot_sprite, NULL);
            first = sfFalse; 
        }
    }
    asprintf(&arrived_str, "Robots arrived: %d/%d", arrived, atoi(sim->nb_robots));
    sfText_setString(sim->str_nb_rooms, arrived_str);
    free(arrived_str);
    sfText_setPosition(sim->str_nb_rooms, (sfVector2f){1575, 50});
    sfRenderWindow_drawText(window, sim->str_nb_rooms, NULL);
    sfRenderWindow_drawText(window, sim->text_nb_tour, NULL);
    print_rooms(sim, sim->str_rooms, window);
    draw_button_list(window, sim->buttons);
    sfRenderWindow_display(window);
}
