/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** main_loop
*/

#include "../../include/bonus.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static void setup_text_rooms(main_struct_t *main_struct)
{
    main_struct->str_nb_rooms = sfText_create();
    sfText_setFont(main_struct->str_nb_rooms, main_struct->main_font);

    char *prefix = "Number of robots : ";
    size_t total_len = strlen(prefix) + strlen(main_struct->nb_robots) + 1;
    char *to_write = malloc(sizeof(char) * total_len);
    strcpy(to_write, prefix);
    strcat(to_write, main_struct->nb_robots);
    sfText_setString(main_struct->str_nb_rooms, to_write);
    sfText_setCharacterSize(main_struct->str_nb_rooms, 30);
    sfText_setColor(main_struct->str_nb_rooms, sfRed);
    sfText_setPosition(main_struct->str_nb_rooms, (sfVector2f){1550, 50});
}

void setup_text_tour(main_struct_t *main_struct)
{
    main_struct->text_nb_tour = sfText_create();
    sfText_setFont(main_struct->text_nb_tour, main_struct->main_font);
    sfText_setCharacterSize(main_struct->text_nb_tour, 30);
    sfText_setColor(main_struct->text_nb_tour, sfRed);
    sfText_setPosition(main_struct->text_nb_tour, (sfVector2f){1740, 100});
}

static void setup_print_name_rooms(main_struct_t *main_struct)
{
    main_struct->str_rooms = sfText_create();
    sfText_setFont(main_struct->str_rooms, main_struct->main_font);
}

static void setup_clock(main_struct_t *main_struct)
{
    main_struct->clock = sfClock_create();
}

static void setup_texture_and_sprite(main_struct_t *main_struct)
{
    main_struct->room_text = sfTexture_createFromFile
        ("bonus/assets/sprite_test-removebg-preview.png", NULL);
    main_struct->room_sprite = sfSprite_create();
    sfSprite_setTexture(main_struct->room_sprite,
        main_struct->room_text, sfTrue);
    sfSprite_setScale(main_struct->room_sprite, (sfVector2f){0.2f, 0.2f});
}

static void setup_links(main_struct_t *main_struct)
{
    main_struct->links = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(main_struct->links, sfLines);
}

int call_functions(main_struct_t *main_struct)
{
    setup_links(main_struct);
    setup_texture_and_sprite(main_struct);
    setup_print_name_rooms(main_struct);
    setup_clock(main_struct);
    setup_text_rooms(main_struct);
    setup_text_tour(main_struct);
    return 0;
}

void update_text_position(robot_t *robot)
{
    sfVector2f text_pos = sfSprite_getPosition(robot->robot_sprite);

    text_pos.y += 5;
    sfText_setPosition(robot->text, text_pos);
}

void draw_all(main_struct_t *main_struct)
{
    sfRenderWindow_clear(main_struct->f, sfBlack);
    for (robot_t *cur = main_struct->robot; cur; cur = cur->next) {
        sfRenderWindow_drawText(main_struct->f, cur->text, NULL);
        sfRenderWindow_drawSprite(main_struct->f, cur->robot_sprite, NULL);
    }
    sfRenderWindow_drawText(main_struct->f, main_struct->str_nb_rooms, NULL);
    sfRenderWindow_drawText(main_struct->f, main_struct->text_nb_tour, NULL);
    print_rooms(main_struct, main_struct->str_rooms);
    print_lines(main_struct->links, main_struct);
    sfRenderWindow_display(main_struct->f);
}

static void update_position(robot_t *cur, int *all_reached, sfVector2f current_pos, sfVector2f target_pos)
{
    float dx = target_pos.x - current_pos.x;
    float dy = target_pos.y - current_pos.y;
    float distance = sqrt(dx * dx + dy * dy);
    float speed = 2.0f;
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

void update_text_tour(main_struct_t *main_struct, int current_index)
{
    char *str = NULL;
    asprintf(&str, "Tour : %d/%d", current_index + 1, main_struct->nb_tour);
    sfText_setString(main_struct->text_nb_tour, str);
    free(str);
}


void update_robots_position(main_struct_t *main_struct, int *index)
{
    int all_reached = 1;
    round_t *tmp = NULL;
    sfVector2f target_pos = {0, 0};
    sfVector2f current_pos = {0, 0};

    for (robot_t *cur = main_struct->robot; cur; cur = cur->next) {
        tmp = find_node(cur, *index);
        target_pos = tmp->pos;
        current_pos = sfSprite_getPosition(cur->robot_sprite);
        update_position(cur, &all_reached, current_pos, target_pos);
    }
    if (all_reached)
        *index += 1;
}

int main_loop(main_struct_t *main_struct)
{
    sfEvent event;
    static int current_index = 0;

    main_struct->f = create_window();
    call_functions(main_struct);
    sfRenderWindow_setFramerateLimit(main_struct->f, 60);
    while (sfRenderWindow_isOpen(main_struct->f)) {
        update_event(main_struct, event);
        if (sfClock_getElapsedTime(main_struct->clock).microseconds > 16667) {
            sfClock_restart(main_struct->clock);
            update_robots_position(main_struct, &current_index);
            update_text_tour(main_struct, current_index);
            draw_all(main_struct);
        }
    }
    return 0;
}