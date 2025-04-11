/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-gabin.wilson
** File description:
** button_state
*/
#include "bonus.h"

void refresh_active_buttons(button_list_t *list, int effect)
{
    for (button_t *button = list->head; button; button = button->next)
        if (button->effect != effect && button->active)
            button->active = 0;
}

void refresh_buttons_state(sfRenderWindow *window, button_list_t *list)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(window, pos, NULL);
    sfFloatRect bounds;

    for (button_t *button = list->head; button; button = button->next) {
        bounds = sfRectangleShape_getGlobalBounds(button->rect);
        if (button->hover == 1)
            button->hover = 0;
        if (sfFloatRect_contains(&bounds, world_pos.x, world_pos.y))
            button->hover = 1;
    }
}
