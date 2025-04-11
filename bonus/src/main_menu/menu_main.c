/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** menu_main
*/
#include "bonus.h"

static char *get_time(char *path)
{
    static char str[64];
    struct stat file_stat;

    if (stat(path, &file_stat) == 0)
        strftime(str, sizeof(str), "%d/%m/%Y %H:%M:%S",
            localtime(&file_stat.st_mtime));
    else
        return "Unknown modif date";
    return str;
}

static void refresh_file_text(menu_t *menu)
{
    char str[256];
    char date_str[64];
    char filepath[256];

    snprintf(filepath, sizeof(filepath), "bonus/test_files/%s",
        menu->files[menu->index]);
    strcpy(date_str, get_time(filepath));
    if (!menu->files)
        return;
    for (button_t *button = menu->list->head; button; button = button->next) {
        if (button->effect == -85 && menu->files && menu->files[0]) {
            snprintf(str, sizeof(str), "%s\n%s",
                    menu->files[menu->index], date_str);
            sfText_setString(button->text, str);
            resize_text(&(button->text), button);
        }
    }
}

static void refresh_menu_button_nbr(menu_t *menu)
{
    char str[25];
    char *words[3] = {"ROBOTS", "ROOMS", "CHANCE OF\nLINK"};

    for (button_t *button = menu->list->head; button; button = button->next) {
        if (button->effect >= 10 && button->effect <= 12 &&
            menu->values[button->effect - 10]) {
            snprintf(str, sizeof(str), "%s : %d",
                words[button->effect - 10], menu->values[button->effect - 10]);
            sfText_setString(button->text, str);
            resize_text(&(button->text), button);
        }
        if (button->effect >= 10 && button->effect <= 12 &&
            !menu->values[button->effect - 10]) {
            sfText_setString(button->text, "Type number...");
            resize_text(&(button->text), button);
        }
    }
}

void print_menu(sfRenderWindow *window, menu_t *menu)
{
    if (!window || !menu)
        return;
    refresh_file_text(menu);
    refresh_menu_button_nbr(menu);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, menu->background, NULL);
    draw_button_list(window, menu->list);
    sfRenderWindow_display(window);
}

int menu_main(sfRenderWindow *window)
{
    menu_t *menu = init_menu();
    int res = 0;

    if (!menu)
        return 84;
    while (menu->state == 0) {
        menu_events(window, menu);
        print_menu(window, menu);
    }
    res = menu->state;
    free_menu(menu);
    return res;
}
