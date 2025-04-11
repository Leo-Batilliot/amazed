/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free_sim
*/
#include "bonus.h"

void free_link_list(link_t *head)
{
    link_t *tmp = NULL;

    for (; head; head = tmp) {
        if (head->array)
            sfVertexArray_destroy(head->array);
        if (head->link_a)
            free(head->link_a);
        if (head->link_b)
            free(head->link_b);
        tmp = head->next;
        free(head);
    }
}

void free_rooms_list(rooms_t *head)
{
    rooms_t *tmp = NULL;

    for (; head; head = tmp) {
        if (head->name_room)
            free(head->name_room);
        tmp = head->next;
        free(head);
    }
}

void free_robots_list(robot_t *head)
{
    robot_t *tmp = NULL;
    round_t *tmpr = NULL;

    for (; head; head = tmp) {
        for (; head->positions; head->positions = tmpr) {
            tmpr = head->positions->next;
            free(head->positions);
        }
        if (head->robot_sprite)
            sfSprite_destroy(head->robot_sprite);
        tmp = head->next;
        free(head);
    }
}

// if (sim->robot_texture)
//     sfTexture_destroy(sim->robot_texture);
// if (sim->room_sprite)
//     sfSprite_destroy(sim->room_sprite);
// if (sim->room_text)
//     sfTexture_destroy(sim->room_text);
// if (sim->text_nb_tour)
//     sfText_destroy(sim->text_nb_tour);
// if (sim->str_rooms)
//     sfText_destroy(sim->str_rooms);
// if (sim->str_nb_rooms)
//     sfText_destroy(sim->str_nb_rooms);
// if (sim->size)
//     free(sim->size);
void free_sim_rest(sim_t *sim)
{
    free_buttons_list(sim->buttons);
}

void free_sim(sim_t *sim)
{
    if (sim->clock)
        sfClock_destroy(sim->clock);
    if (sim->link)
        free_link_list(sim->link);
    if (sim->robot)
        free_robots_list(sim->robot);
    if (sim->list)
        free_rooms_list(sim->list);
    if (sim->main_font)
        sfFont_destroy(sim->main_font);
    if (sim->nb_robots)
        free(sim->nb_robots);
    free_sim_rest(sim);
    free(sim);
}
