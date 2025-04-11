/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** event
*/
#include "bonus.h"

static void activate_sim_button(int effect, sim_t *sim, sfRenderWindow *window)
{
    (void) window;
    if (effect == 84)
        sim->state = 84;
    if (effect == 2 && sim->speed < 20)
        sim->speed += 1;
    if (effect == -2 && sim->speed >= 1)
        sim->speed -= 1;
}

static void sim_mouse(sim_t *sim, sfRenderWindow *window)
{
    for (button_t *button = sim->buttons->head; button; button = button->next) {
        if (button->hover && (!button->active || !button->permanant)) {
            button->active = 1;
            refresh_active_buttons(sim->buttons, button->effect);
            return activate_sim_button(button->effect, sim, window);
        }
        if (button->hover && button->active)
            button->active = 0;
    }
}

void sim_events(sim_t *sim, sfRenderWindow *window)
{
    sfEvent event;

    refresh_buttons_state(window, sim->buttons);
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sim->state = 84;
        if ((event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape))
            sim->state = 1;
        if (event.type == sfEvtMouseButtonPressed)
            sim_mouse(sim, window);
    }
}