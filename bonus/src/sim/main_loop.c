/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** main_loop
*/
#include "bonus.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static void setup_text_rooms(sim_t *sim)
{
    sim->str_nb_rooms = sfText_create();
    sfText_setFont(sim->str_nb_rooms, sim->main_font);

    char *prefix = "Number of robots : ";
    size_t total_len = strlen(prefix) + strlen(sim->nb_robots) + 1;
    char *to_write = malloc(sizeof(char) * total_len);
    strcpy(to_write, prefix);
    strcat(to_write, sim->nb_robots);
    sfText_setString(sim->str_nb_rooms, to_write);
    sfText_setCharacterSize(sim->str_nb_rooms, 30);
    sfText_setColor(sim->str_nb_rooms, sfRed);
    sfText_setPosition(sim->str_nb_rooms, (sfVector2f){1550, 50});
}

void setup_text_tour(sim_t *sim)
{
    sim->text_nb_tour = sfText_create();
    sfText_setFont(sim->text_nb_tour, sim->main_font);
    sfText_setCharacterSize(sim->text_nb_tour, 30);
    sfText_setColor(sim->text_nb_tour, sfRed);
    sfText_setPosition(sim->text_nb_tour, (sfVector2f){1740, 100});
}

static void setup_print_name_rooms(sim_t *sim)
{
    sim->str_rooms = sfText_create();
    sfText_setFont(sim->str_rooms, sim->main_font);
}

static void setup_clock(sim_t *sim)
{
    sim->clock = sfClock_create();
}

static void setup_texture_and_sprite(sim_t *sim)
{
    sim->room_text = sfTexture_createFromFile
        ("bonus/assets/flag.png", NULL);
    sim->room_sprite = sfSprite_create();
    sfSprite_setTexture(sim->room_sprite,
        sim->room_text, sfTrue);
    sfSprite_setScale(sim->room_sprite, (sfVector2f){0.2f, 0.2f});
}

int call_functions(sim_t *sim)
{
    setup_texture_and_sprite(sim);
    setup_print_name_rooms(sim);
    setup_clock(sim);
    setup_text_rooms(sim);
    setup_text_tour(sim);
    return 0;
}

void update_text_position(robot_t *robot)
{
    sfVector2f text_pos = sfSprite_getPosition(robot->robot_sprite);

    text_pos.y += 5;
    sfText_setPosition(robot->text, text_pos);
}

static void update_position(robot_t *cur, int *all_reached, sfVector2f current_pos, sfVector2f target_pos, int sspeed)
{
    float dx = target_pos.x - current_pos.x;
    float dy = target_pos.y - current_pos.y;
    float distance = sqrt(dx * dx + dy * dy);
    float speed = sspeed;
    float normalized_dx = 0;
    float normalized_dy = 0;

    if (distance > 1.0f) {
        *all_reached = 0;
        if (distance <= speed) {
            current_pos = target_pos;
        } else {
            normalized_dx = dx / distance;
            normalized_dy = dy / distance;
            current_pos.x += normalized_dx * speed;
            current_pos.y += normalized_dy * speed;
        }
        sfSprite_setPosition(cur->robot_sprite, current_pos);
        update_text_position(cur);
    } else if (distance > 0) {
        sfSprite_setPosition(cur->robot_sprite, target_pos);
        update_text_position(cur);
    }
}

void update_text_tour(sim_t *sim, int current_index)
{
    char *str = NULL;
    asprintf(&str, "Move %d/%d", current_index + 1, sim->nb_tour);
    sfText_setString(sim->text_nb_tour, str);
    free(str);
}


void update_robots_position(sim_t *sim, int *index)
{
    int all_reached = 1;
    round_t *tmp = NULL;
    sfVector2f target_pos = {0, 0};
    sfVector2f current_pos = {0, 0};

    for (robot_t *cur = sim->robot; cur; cur = cur->next) {
        tmp = find_node(cur, *index);
        target_pos = tmp->pos;
        current_pos = sfSprite_getPosition(cur->robot_sprite);
        update_position(cur, &all_reached, current_pos, target_pos, sim->speed);
    }
    if (all_reached)
        *index += 1;
}

int main_loop(sim_t *sim, sfRenderWindow *window)
{
    static int current_index = 0;

    call_functions(sim);
    while (sim->state == 1) {
        sim_events(sim, window);
        if (sfClock_getElapsedTime(sim->clock).microseconds > 16667) {
            sfClock_restart(sim->clock);
            update_robots_position(sim, &current_index);
            if (current_index == sim->nb_tour) {
                sim->state = 84;
                break;
            }
            update_text_tour(sim, current_index);
            draw_all(sim, window);
        }
    }
    return sim->state;
}