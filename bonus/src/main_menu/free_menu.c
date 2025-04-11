/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_menu
*/
#include "bonus.h"

void free_menu(menu_t *menu)
{
    if (!menu)
        return;
    if (menu->background)
        sfSprite_destroy(menu->background);
    if (menu->texture)
        sfTexture_destroy(menu->texture);
    if (menu->loading)
        sfText_destroy(menu->loading);
    if (menu->list)
        free_buttons_list(menu->list);
    if (menu->font)
        sfFont_destroy(menu->font);
    if (menu->files)
        free_array((void **)menu->files);
    free(menu);
}
