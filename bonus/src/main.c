/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** main
*/

#include "../include/bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <strings.h>
#include <math.h>

sfRenderWindow *create_window(void)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "BONUS A MAZED", sfResize | sfClose, NULL);

    if (!window) {
        dprintf(2, "Window creation failed.\n");
        return NULL;
    }
    return window;
}

static int update_scale(main_struct_t *main_struct, float max_x, float max_y)
{
    float scale_x = (1920.0f - 200.0f) / max_x;
    float scale_y = (1080.0f - 200.0f) / max_y;

    for (rooms_t *tmp = main_struct->list; tmp; tmp = tmp->next) {
        tmp->pos.x = (int)(tmp->pos.x * scale_x + 100);
        tmp->pos.y = (int)(tmp->pos.y * scale_y + 100);
    }
    return 0;
}

int get_min_max(main_struct_t *main_struct)
{
    float min_x = main_struct->list->pos.x;
    float max_x = main_struct->list->pos.x;
    float min_y = main_struct->list->pos.y;
    float max_y = main_struct->list->pos.y;

    for (rooms_t *tmp = main_struct->list; tmp; tmp = tmp->next) {
        if (tmp->pos.x < min_x)
            min_x = tmp->pos.x;
        if (tmp->pos.x > max_x)
            max_x = tmp->pos.x;
        if (tmp->pos.y < min_y)
            min_y = tmp->pos.y;
        if (tmp->pos.y > max_y)
            max_y = tmp->pos.y;
    }
    max_x -= min_x;
    max_y -= min_y;
    update_scale(main_struct, max_x, max_y);
    return 0;
}

sfVector2f ret_vect(main_struct_t *main_struct, int end)
{
    for (rooms_t *tmp = main_struct->list; tmp; tmp = tmp->next) {
        if (tmp->is_start == end)
            return tmp->pos;
    }
    return (sfVector2f){0, 0};
}

sfVector2f ret_pos(char *to_find, main_struct_t *main_struct)
{
    for (rooms_t *tmp = main_struct->list; tmp; tmp = tmp->next) {
        if (!strcmp(tmp->name_room, to_find)) {
            return tmp->pos;
        }
    }
    return (sfVector2f){0, 0};
}

int create_list_robot(main_struct_t *main_struct)
{
    robot_t *node = NULL;
    sfTexture *texture = sfTexture_createFromFile("bonus/assets/sprite_robot-removebg-preview.png", NULL);
    int id = 0;

    for (int i = 0; i < atoi(main_struct->nb_robots); i++) {
        node = malloc(sizeof(robot_t));
        if (!node)
            return -1;
        id = i + 1;
        asprintf(&node->id, "%d", id);
        node->robot_sprite = sfSprite_create();
        sfSprite_setTexture(node->robot_sprite, texture, sfTrue);
        node->last_pos = ret_vect(main_struct, 1);
        sfVector2u size = sfTexture_getSize(texture);
        sfSprite_setOrigin(node->robot_sprite, (sfVector2f){size.x / 2.5f, size.y / 1.0f});
        sfSprite_setScale(node->robot_sprite, (sfVector2f){0.10f, 0.10f});
        sfSprite_setPosition(node->robot_sprite, node->last_pos);
        node->text = sfText_create();
        sfText_setFont(node->text, main_struct->main_font);
        sfText_setCharacterSize(node->text, 24);
        sfText_setColor(node->text, sfWhite);
        sfText_setString(node->text, node->id);
        sfVector2f text_pos = node->last_pos;
        text_pos.y += 5;
        sfText_setPosition(node->text, text_pos);
        node->robots = NULL;
        node->next = main_struct->robot;
        main_struct->robot = node;
    }
    return 0;
}

round_t *find_node(robot_t *robot, int count)
{
    int i = 0;
    round_t *cur = robot->robots;

    while (cur != NULL && i < count) {
        cur = cur->next;
        i++;
    }
    return cur;
}

int main(void)
{
    main_struct_t *main_struct = malloc(sizeof(main_struct_t));
    FILE *fd = NULL;

    if (!main_struct)
        return 84;
    main_struct->list = NULL;
    main_struct->link = NULL;
    main_struct->robot = NULL;
    main_struct->nb_tour = 0;
    fd = fopen("bonus/input.txt", "r");
    if (!fd) {
        printf("%s\n", strerror(errno));
        return 84;
    }
    main_struct->main_font = sfFont_createFromFile("bonus/font/Super Kinds.ttf");
    parsing_file(fd, main_struct);
    main_loop(main_struct);
    return 0;
}