/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <dirent.h>
    #include <SFML/Graphics.h>
    #include <SFML/Window.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
    #include <GL/glu.h>
    #include <sys/stat.h>
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <time.h>

typedef struct button_data_s {
    int sizey;
    int sizex;
    int posx;
    int posy;
    char *path;
    int effect;
    int permanant;
    char *text;
    sfFont *font;
    char *hover;
} button_data_t;

typedef struct button_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfText *text;
    sfText *htext;
    sfRectangleShape *rect;
    int permanant;
    int active;
    int hover;
    int effect;
    sfVector2f pos;
    sfVector2f size;
    struct button_s *next;
} button_t;

typedef struct button_list_s {
    button_t *head;
} button_list_t;

typedef struct menu_s {
    int values[3];
    int **map;
    int index;
    char **files;
    int count;
    button_list_t *list;
    sfSprite *background;
    sfTexture *texture;
    sfFont *font;
    sfText *loading;
    int state;
} menu_t;

typedef struct rooms_s {
    int start_end;
    char *name_room;
    sfVector2f pos;
    struct rooms_s *next;
} rooms_t;

typedef struct link_s {
    char *link_a;
    char *link_b;
    sfVertexArray *array;
    struct link_s *next;
} link_t;

typedef struct round_s {
    sfVector2f pos;
    struct round_s *next;
} round_t;

typedef struct robot_s {
    char *id;
    sfSprite *robot_sprite;
    round_t *positions;
    sfText *text;
    sfVector2f last_pos;
    struct robot_s *next;
} robot_t;

typedef struct sim_s {
    char *size;
    char *nb_robots;
    int nb_tour;
    int state;
    int speed;
    sfText *text_nb_tour;
    sfSprite *room_sprite;
    sfTexture *room_text;
    sfFont *main_font;
    sfText *str_rooms;
    sfText *str_nb_rooms;
    sfClock *clock;
    link_t *link;
    rooms_t *list;
    robot_t *robot;
    sfTexture *robot_texture;
    button_list_t *buttons;
} sim_t;

/* MENU */
void free_menu(menu_t *);
int simulation_main(sfRenderWindow *);
int menu_main(sfRenderWindow *);
void menu_events(sfRenderWindow *, menu_t *);
menu_t *init_menu(void);

/* SIM */
void free_sim(sim_t *sim);
sim_t *init_sim(void);
void sim_events(sim_t *, sfRenderWindow *);
int main_loop(sim_t *, sfRenderWindow *);
void draw_all(sim_t *sim, sfRenderWindow *window);
sfVector2f get_pos(char *to_find, sim_t *sim);
int parse_file(FILE *fd, sim_t *sim);

int parsing_file(FILE *fd, sim_t *sim);
int get_min_max(sim_t *sim);
int add_to_link(char **array, sim_t *sim);
int create_list_robot(sim_t *sim);
int add_pos_to_robot(robot_t *robot, sfVector2f pos);
round_t *find_node(robot_t *robot, int count);

/* LIB */
void free_array_until(char **, int);
int my_free(void *);
int free_array(void **);
int my_array_len(char **);
char **split_string(char const *, char const *);
char *my_strncpy(char *, char const *, int);
int add_to_node(sim_t *, int[2], char **);

/* UTILS */
void add_button(button_list_t *list, button_t *button);
button_list_t *init_buttons_list(void);
button_t *load_button(button_data_t data);
void free_buttons_list(button_list_t *list);
void draw_button_list(sfRenderWindow *window, button_list_t *list);
void refresh_buttons_state(sfRenderWindow *window, button_list_t *list);
void refresh_active_buttons(button_list_t *list, int effect);
void resize_text(sfText **text, button_t *button);

#endif /* !MY_H_ */
