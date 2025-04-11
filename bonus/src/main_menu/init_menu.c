/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init_menu
*/
#include "bonus.h"

static void init_load_buttons(menu_t *menu)
{
    add_button(menu->list, load_button((button_data_t)
        {500, 100, 480, 500, "bonus/assets/button.png",
        -85, 0, "No files saved", menu->font, NULL}));
    add_button(menu->list, load_button((button_data_t)
        {300, 100, 480, 700, "bonus/assets/load.png",
        2, 0, NULL, menu->font, NULL}));
    add_button(menu->list, load_button((button_data_t)
        {100, 100, 180, 500, "bonus/assets/left.png",
        -3, 0, NULL, menu->font, NULL}));
    add_button(menu->list, load_button((button_data_t)
        {100, 100, 780, 500, "bonus/assets/right.png",
        3, 0, NULL, menu->font, NULL}));
}

static void init_new_buttons(menu_t *menu)
{
    add_button(menu->list, load_button((button_data_t)
        {300, 100, 1440, 700, "bonus/assets/new.png",
        1, 0, NULL, menu->font, NULL}));
    add_button(menu->list, load_button((button_data_t)
        {400, 100, 1440, 550, "bonus/assets/textbox.png",
        10, 1, "...", menu->font, NULL}));
    add_button(menu->list, load_button((button_data_t)
        {400, 100, 1440, 400, "bonus/assets/textbox.png",
        11, 1, "...", menu->font, NULL}));
    add_button(menu->list, load_button((button_data_t)
        {400, 100, 1440, 250, "bonus/assets/textbox.png",
        12, 1, "...", menu->font, NULL}));
}

static void menu_buttons(menu_t *menu)
{
    menu->list = init_buttons_list();
    if (!menu->list)
        return;
    add_button(menu->list, load_button((button_data_t)
        {100, 100, 1870, 50, "bonus/assets/close.png",
        84, 0, NULL, menu->font, NULL}));
    init_new_buttons(menu);
    init_load_buttons(menu);
}

static void menu_text(menu_t *menu)
{
    sfFloatRect tb;

    menu->font = sfFont_createFromFile("bonus/assets/font.ttf");
    if (!menu->font)
        return;
    menu->loading = sfText_create();
    if (!menu->loading)
        return;
    sfText_setCharacterSize(menu->loading, 100);
    sfText_setColor(menu->loading, sfWhite);
    sfText_setOutlineColor(menu->loading, sfBlack);
    sfText_setOutlineThickness(menu->loading, 3);
    tb = sfText_getLocalBounds(menu->loading);
    sfText_setScale(menu->loading, (sfVector2f){1000 /
        tb.width / 1.5, 500 / tb.height / 1.5});
    tb = sfText_getLocalBounds(menu->loading);
    sfText_setOrigin(menu->loading, (sfVector2f) {tb.left + tb.width / 2,
        tb.top + tb.height / 2});
}

static void init_menu_files(menu_t *menu)
{
    DIR *dir;

    dir = opendir("bonus/test_files");
    if (!dir)
        return;
    menu->files = malloc(sizeof(char *) * 20);
    if (!menu->files) {
        closedir(dir);
        return;
    }
    for (struct dirent *entry = readdir(dir); entry &&
        menu->count < 20; entry = readdir(dir)) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;
        menu->files[menu->count] = strdup(entry->d_name);
        if (!menu->files[menu->count])
            return free_array_until(menu->files, menu->count);
        menu->count++;
    }
    closedir(dir);
}

static void menu_variables(menu_t *menu)
{
    for (int i = 0; i < 3; i++)
        menu->values[i] = 0;
    menu->map = NULL;
    menu->background = NULL;
    menu->font = NULL;
    menu->list = NULL;
    menu->files = NULL;
    menu->index = 0;
    menu->count = 0;
    menu->texture = NULL;
    init_menu_files(menu);
    if (!menu->files) {
        menu->files = NULL;
        menu->count = 0;
    } else
        menu->files[menu->count] = NULL;
}

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    if (!menu)
        return NULL;
    menu_variables(menu);
    menu_text(menu);
    menu->texture = sfTexture_createFromFile("bonus/assets/menu.jpg", NULL);
    menu_buttons(menu);
    if (!menu->font || !menu->texture || !menu->list ||
        !menu->list->head || !menu->loading) {
        free_menu(menu);
        return NULL;
    }
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, menu->texture, sfTrue);
    menu->state = 0;
    return menu;
}
