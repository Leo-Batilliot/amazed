/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** init
*/
#include "bonus.h"

sfVector2f get_vect(sim_t *sim)
{
    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next)
        if (tmp->start_end == 1)
            return tmp->pos;
    return (sfVector2f){0, 0};
}

static int init_robot_sprite(robot_t *node, sim_t *sim)
{
    node->robot_sprite = sfSprite_create();
    if (!node->robot_sprite)
        return 1;
    sfSprite_setTexture(node->robot_sprite, sim->robot_texture, sfTrue);
    node->last_pos = get_vect(sim);
    sfVector2u size = sfTexture_getSize(sim->robot_texture);
    sfSprite_setOrigin(node->robot_sprite, (sfVector2f)
        {size.x / 2.5f, size.y / 1.0f});
    sfSprite_setScale(node->robot_sprite, (sfVector2f){0.10f, 0.10f});
    sfSprite_setPosition(node->robot_sprite, node->last_pos);
    return 0;
}

static int init_robot_text(robot_t *node, sim_t *sim)
{
    node->text = sfText_create();
    if (!node->text)
        return 1;
    sfText_setFont(node->text, sim->main_font);
    sfText_setCharacterSize(node->text, 24);
    sfText_setColor(node->text, sfWhite);
    sfText_setString(node->text, node->id);
    sfVector2f text_pos = node->last_pos;
    text_pos.y += 5;
    sfText_setPosition(node->text, text_pos);
    return 0;
}

static void init_robot(robot_t *node, sim_t *sim, int i)
{
    asprintf(&node->id, "%d", i + 1);

    if (init_robot_sprite(node, sim)) {
        free(node);
        return;
    }
    if (init_robot_text(node, sim)) {
        sfSprite_destroy(node->robot_sprite);
        free(node);
        return;
    }
    node->positions = NULL;
    node->next = sim->robot;
    sim->robot = node;
}

int create_list_robot(sim_t *sim)
{
    robot_t *node = NULL;
    sim->robot_texture = sfTexture_createFromFile(
        "bonus/assets/robot.png", NULL);

    if (!sim->robot_texture)
        return 1;
    for (int i = 0; i < atoi(sim->nb_robots); i++) {
        node = malloc(sizeof(robot_t));
        if (!node)
            return -1;
        init_robot(node, sim, i);
    }
    return 0;
}

static void init_sim_buttons(sim_t *sim)
{
    sim->buttons = init_buttons_list();
    if (!sim->buttons)
        return;
    add_button(sim->buttons, load_button((button_data_t)
        {70, 70, 35, 50, "bonus/assets/-.png",
        -2, 0, NULL, sim->main_font, NULL}));
    add_button(sim->buttons, load_button((button_data_t)
        {200, 70, 170, 50, "bonus/assets/button.png",
        -85, 0, "SPEED", sim->main_font, "ROBOTS\nSPEED"}));
    add_button(sim->buttons, load_button((button_data_t)
        {70, 70, 305, 50, "bonus/assets/+.png",
        2, 0, NULL, sim->main_font, NULL}));
}

sim_t *init_sim(void)
{
    sim_t *sim = malloc(sizeof(sim_t));

    if (!sim)
        return NULL;
    sim->main_font = sfFont_createFromFile("bonus/assets/font.ttf");
    init_sim_buttons(sim);
    if (!sim->main_font || !sim->buttons) {
        free(sim);
        return NULL;
    }
    sim->list = NULL;
    sim->link = NULL;
    sim->robot = NULL;
    sim->speed = 3;
    sim->nb_tour = 0;
    sim->state = 1;
    return sim;
}