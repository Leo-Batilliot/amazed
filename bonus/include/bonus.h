/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <SFML/Audio.h>
    #include <SFML/Graphics.h>

typedef struct rooms_s {
    int is_start;
    int is_end;
    char *name_room;
    sfVector2f pos;
    struct rooms_s *next;
} rooms_t;

typedef struct link_s {
    char *link_a;
    char *link_b;
    struct link_s *next;
} link_t;

typedef struct round_s {
    sfVector2f pos;
    struct round_s *next;
} round_t;

typedef struct robot_s {
    char *id;
    sfSprite *robot_sprite;
    round_t *robots;
    sfText *text;
    sfVector2f last_pos;
    struct robot_s *next;
} robot_t;

typedef struct {
    char *size;
    char *nb_robots;
    int nb_tour;
    sfText *text_nb_tour;
    sfRenderWindow *f;
    sfSprite *room_sprite;
    sfTexture *room_text;
    sfFont *main_font;
    sfText *str_rooms;
    sfText *str_nb_rooms;
    sfVertexArray *links;
    sfClock *clock;
    link_t *link;
    rooms_t *list;
    robot_t *robot;
} main_struct_t;

char **split_string(char const *str, char const *delim);
char *my_strncpy(char *dest, char const *src, int n);

// PROJECT

void print_rooms(main_struct_t *main_struct, sfText *text);
sfVector2f ret_pos(char *to_find, main_struct_t *main_struct);
void print_lines(sfVertexArray *_link, main_struct_t *main_struct);
int update_event(main_struct_t *main_struct, sfEvent event);
int parsing_file(FILE *fd, main_struct_t *main_struct);
int get_min_max(main_struct_t *main_struct);
int add_to_link(char **array, main_struct_t *main_struct);
int create_list_robot(main_struct_t *main_struct);
int add_to_node(main_struct_t *main_struct, int _start, int _end, char **array);
int add_pos_to_robot(robot_t *robot, sfVector2f pos);
int main_loop(main_struct_t *main_struct);
sfRenderWindow *create_window(void);
round_t *find_node(robot_t *robot, int count);

#endif /* !MY_H_ */
