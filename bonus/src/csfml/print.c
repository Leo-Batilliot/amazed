/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** print
*/

#include "../../include/bonus.h"

void print_rooms(main_struct_t *main_struct, sfText *text)
{
    for (rooms_t *tmp = main_struct->list; tmp; tmp = tmp->next) {
        sfVector2u size = sfTexture_getSize(main_struct->room_text);
        sfSprite_setOrigin(main_struct->room_sprite, (sfVector2f){size.x / 5.0f, size.y});
        sfSprite_setPosition(main_struct->room_sprite, tmp->pos);
        sfRenderWindow_drawSprite(main_struct->f, main_struct->room_sprite, NULL);
        sfText_setString(text, tmp->name_room);
        sfText_setPosition(text, (sfVector2f){tmp->pos.x + 15, tmp->pos.y});
        sfText_setColor(main_struct->str_rooms, sfWhite);
        if (tmp->is_end == 1)
            sfText_setColor(text, sfRed);
        if (tmp->is_start == 1)
            sfText_setColor(text, sfGreen);
        sfRenderWindow_drawText(main_struct->f, text, NULL);
    }
}

void print_lines(sfVertexArray *_link, main_struct_t *main_struct)
{
    for (link_t *tmp = main_struct->link; tmp; tmp = tmp->next) {
        sfVertex p1 = {.position = ret_pos(tmp->link_a, main_struct), .color = sfWhite};
        sfVertex p2 = {.position = ret_pos(tmp->link_b, main_struct), .color = sfWhite};
        sfVertexArray_append(_link, p1);
        sfVertexArray_append(_link, p2);
        sfRenderWindow_drawVertexArray(main_struct->f, _link, NULL);
    }
}