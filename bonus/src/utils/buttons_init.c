/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-gabin.wilson
** File description:
** buttons
*/
#include "bonus.h"

static void set_button_pos(button_t *button)
{
    sfFloatRect sprite_bounds;

    if (!button)
        return;
    sprite_bounds = sfSprite_getLocalBounds(button->sprite);
    sfSprite_setScale(button->sprite, (sfVector2f){button->size.x /
        sprite_bounds.width, button->size.y / sprite_bounds.height});
    sprite_bounds = sfSprite_getLocalBounds(button->sprite);
    sfSprite_setOrigin(button->sprite, (sfVector2f){sprite_bounds.width / 2,
        sprite_bounds.height / 2});
    sfSprite_setPosition(button->sprite, button->pos);
}

static int set_button_sprite(button_t *button, char *path)
{
    button->texture = sfTexture_createFromFile(path, NULL);
    if (!button->texture) {
        free(button);
        return 84;
    }
    button->sprite = sfSprite_create();
    if (!button->sprite) {
        sfTexture_destroy(button->texture);
        free(button);
        return 84;
    }
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    return 0;
}

static int set_button_rectangle(button_t *button)
{
    button->rect = sfRectangleShape_create();
    if (!button->rect) {
        sfTexture_destroy(button->texture);
        sfSprite_destroy(button->sprite);
        free(button);
        return 84;
    }
    sfRectangleShape_setSize(button->rect, button->size);
    sfRectangleShape_setOrigin(button->rect, (sfVector2f)
        {button->size.x / 2, button->size.y / 2});
    sfRectangleShape_setPosition(button->rect, button->pos);
    sfRectangleShape_setFillColor(button->rect, (sfColor){0, 0, 0, 0});
    return 0;
}

static sfText *set_button_text(sfFont *font, button_t *button, char *text,
    int opt)
{
    sfText *stext = sfText_create();

    if (!stext)
        return NULL;
    sfText_setFont(stext, font);
    if (opt)
        sfText_setColor(stext, sfBlack);
    else
        sfText_setColor(stext, sfWhite);
    sfText_setString(stext, text);
    resize_text(&stext, button);
    return stext;
}

static void set_base_buttons_values(button_t *button, button_data_t data)
{
    button->active = 0;
    button->permanant = data.permanant;
    button->effect = data.effect;
    button->hover = 0;
    button->text = NULL;
    button->htext = NULL;
    button->pos = (sfVector2f) {data.posx, data.posy};
    button->size = (sfVector2f) {data.sizey, data.sizex};
    button->next = NULL;
}

void resize_text(sfText **text, button_t *button)
{
    sfFloatRect text_bounds;

    sfText_setCharacterSize(*text, 100);
    text_bounds = sfText_getLocalBounds(*text);
    sfText_setScale(*text, (sfVector2f){button->size.x /
        text_bounds.width / 1.5, button->size.y / text_bounds.height / 1.5});
    text_bounds = sfText_getLocalBounds(*text);
    sfText_setOrigin(*text, (sfVector2f)
        {text_bounds.left + text_bounds.width / 2,
        text_bounds.top + text_bounds.height / 2});
    sfText_setPosition(*text, button->pos);
}

button_t *load_button(button_data_t data)
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    set_base_buttons_values(button, data);
    if (set_button_sprite(button, data.path) == 84)
        return NULL;
    if (set_button_rectangle(button) == 84)
        return NULL;
    if (data.text)
        button->text = set_button_text(data.font, button, data.text, 1);
    if (data.hover)
        button->htext = set_button_text(data.font, button, data.hover, 0);
    set_button_pos(button);
    return button;
}

void add_button(button_list_t *list, button_t *button)
{
    if (!list || !button)
        return;
    button->next = list->head;
    list->head = button;
}

button_list_t *init_buttons_list(void)
{
    button_list_t *list = malloc(sizeof(button_list_t));

    if (!list)
        return NULL;
    list->head = NULL;
    return list;
}
