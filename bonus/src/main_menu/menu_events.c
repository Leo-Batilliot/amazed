/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** menu_events
*/
#include "bonus.h"

static int load_file(menu_t *menu)
{
    char cmd[256];

    if (!strcmp(menu->files[menu->index], "program_input.txt"))
        return 0;
    snprintf(cmd, sizeof(cmd),
        "cp bonus/test_files/%s bonus/test_files/program_input.txt",
        menu->files[menu->index]);
    return system(cmd);
}

static int create_file(int values[3], menu_t *menu, sfRenderWindow *window)
{
    char name[64] = "bonus/test_files/test1.txt";
    char cmd[256];

    if (!values[0] || !values[1] || !values[2]) {
        printf("MISSING VALUES FOR SIMULATION\n");
        return 1;
    }
    for (int i = 2; !access(name, F_OK); i++)
        snprintf(name, sizeof(name), "bonus/test_files/test%d.txt", i);
    snprintf(cmd, sizeof(cmd), "./laby_gen.pl %d %d %d | ./amazed > %s",
        values[0], values[2], values[1], name);
    sfRenderWindow_drawText(window, menu->loading, NULL);
    sfRenderWindow_display(window);
    if (system(cmd) != 0) {
        remove(name);
        return 1;
    }
    snprintf(cmd, sizeof(cmd), "cp %s bonus/test_files/program_input.txt",
        name);
    return system(cmd);
}

static int closest_index(char **files, int max, int index, int opt)
{
    if (!files || max <= 0)
        return 0;
    for (int i = index - 1; i >= 0 && opt == 1; i--)
        if (files[i])
            return i;
    for (int i = max - 1; i > index && opt == 1; i--)
        if (files[i])
            return i;
    for (int i = index + 1; i < max && opt == 0; i++)
        if (files[i])
            return i;
    for (int i = 0; i < index && opt == 0; i++)
        if (files[i])
            return i;
    return index;
}

static void activate_menu_button(int effect, menu_t *menu, sfRenderWindow *window)
{
    if (effect == 84)
        menu->state = 84;
    if (effect == 3)
        menu->index = closest_index(menu->files, menu->count, menu->index, 0);
    if (effect == -3)
        menu->index = closest_index(menu->files, menu->count, menu->index, 1);
    if (effect == 1)
        if (!create_file(menu->values, menu, window))
            menu->state = 1;
    if (effect == 2)
        if (!load_file(menu))
            menu->state = 1;
}

static void menu_mouse(menu_t *menu, sfRenderWindow *window)
{
    for (button_t *button = menu->list->head; button; button = button->next) {
        if (button->hover && (!button->active || !button->permanant)) {
            button->active = 1;
            refresh_active_buttons(menu->list, button->effect);
            return activate_menu_button(button->effect, menu, window);
        }
        if (button->hover && button->active)
            button->active = 0;
    }
}

static void menu_keyboard_input(sfEvent event, int *nb)
{
    if (*nb > 0 && event.text.unicode == 8) {
        *nb /= 10;
        return;
    }
    if ((char) event.text.unicode >= '0' && (char) event.text.unicode <= '9')
        if (*nb < 100)
            *nb = (*nb * 10) + (char) event.text.unicode - '0';
}

static void textbox_active(menu_t *menu, sfEvent event)
{
    for (button_t *tmp = menu->list->head; tmp; tmp = tmp->next)
        if (tmp->active && tmp->effect >= 10 && tmp->effect <= 12)
            menu_keyboard_input(event, &(menu->values[tmp->effect - 10]));
}

void menu_events(sfRenderWindow *window, menu_t *menu)
{
    sfEvent event;

    refresh_buttons_state(window, menu->list);
    while (sfRenderWindow_pollEvent(window, &event)) {
        if ((event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) ||
            event.type == sfEvtClosed)
            menu->state = 84;
        if (event.type == sfEvtTextEntered)
            textbox_active(menu, event);
        if (event.type == sfEvtMouseButtonPressed)
            menu_mouse(menu, window);
    }
}
