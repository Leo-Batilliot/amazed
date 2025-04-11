/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-gabin.wilson
** File description:
** buttons_print
*/
#include "bonus.h"

static sfColor get_rect_color(button_t *button)
{
    if (button->active && button->effect >= 10)
        return (sfColor) {0, 0, 0, 85};
    if (button->active && button->permanant && button->effect >= - 84)
        return (sfColor) {0, 255, 0, 90};
    if (button->hover && button->effect >= - 84) {
        if (button->permanant)
            return (sfColor) {0, 0, 0, 70};
        return (sfColor) {0, 0, 0, 60};
    }
    return (sfColor) {0, 0, 0, 0};
}

void draw_button_list(sfRenderWindow *window, button_list_t *list)
{
    for (button_t *button = list->head; button; button = button->next) {
        sfRenderWindow_drawSprite(window, button->sprite, NULL);
        sfRectangleShape_setFillColor(button->rect, get_rect_color(button));
        sfRenderWindow_drawRectangleShape(window, button->rect, NULL);
        if ((!button->hover || !button->htext) && button->text)
            sfRenderWindow_drawText(window, button->text, NULL);
        if (button->hover && button->htext)
            sfRenderWindow_drawText(window, button->htext, NULL);
    }
}
