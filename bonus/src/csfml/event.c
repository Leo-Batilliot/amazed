/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/

#include "../../include/bonus.h"

int update_event(main_struct_t *main_struct, sfEvent event)
{
    while (sfRenderWindow_pollEvent(main_struct->f, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(main_struct->f);
    }
    return 0;
}