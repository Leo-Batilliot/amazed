/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-gabin.wilson
** File description:
** buttons_free
*/
#include "bonus.h"

void free_button(button_t *button)
{
    if (!button)
        return;
    if (button->sprite)
        sfSprite_destroy(button->sprite);
    if (button->texture)
        sfTexture_destroy(button->texture);
    if (button->text)
        sfText_destroy(button->text);
    if (button->rect)
        sfRectangleShape_destroy(button->rect);
    if (button->htext)
        sfText_destroy(button->htext);
    free(button);
}

void free_buttons_list(button_list_t *list)
{
    button_t *save = NULL;

    if (!list)
        return;
    for (button_t *button = list->head; button;) {
        save = button->next;
        free_button(button);
        button = save;
    }
    free(list);
}
