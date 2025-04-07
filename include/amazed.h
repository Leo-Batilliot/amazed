/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** amaze
*/


#ifndef AMAZED_H_
    #define AMAZED_H_

/*    STRUCTURES    */

typedef struct path_s {
    struct room_s *room;
    int distance;
    int score;
    struct path_s *prev;
} path_t;

typedef struct path_list_s {
    struct room_s *start;
    struct room_s *end;
    struct linked_list_s *possible_paths;
    struct path_s *path;
} path_list_t;

typedef struct algo_s {
    path_t *path_wait;
    path_t *path;
    int path_wait_cost;
    int path_cost;
    struct room_s *room;
} algo_t;

typedef struct robot_s {
    struct room_s *room;
    int nbr;
    struct robot_s *prev;
    struct robot_s *next;
} robot_t;

typedef struct link_s {
    struct room_s *room;
    struct link_s *next_link;
} link_t;

typedef struct room_s { 
    char *room_name;
    robot_t *robot;
    int posx;
    int posy;
    int waiting;
    int visited;
    struct link_s *links_list;
    struct room_s *prev;
    struct room_s *next;
} room_t;

typedef struct maze_s {
    robot_t *robots_list;
    struct room_s *rooms_list;
    struct room_s *start;
    struct room_s *end;
    int nb_robots;
    int return_value;
} maze_t;

typedef struct linked_list_s {
    void *data;
    struct linked_list_s *next;
} linked_list_t;

/*    MAIN FUNCTIONS    */
int algo_main(maze_t *maze);
maze_t *init_maze_and_parse(void);
room_t *get_best_room(room_t *, robot_t *, room_t *);

/*    FUNCTIONS    */
int free_maze(maze_t *maze);
int get_robots_numbers(maze_t *, linked_list_t **);
int parse_link(maze_t *, char *, int);
int parse_room(maze_t *, char **, int, int [2]);
path_t *get_best_path(room_t *, room_t *, int);

/*    INIT    */
path_t *init_path(room_t *);
robot_t *init_robots_list(room_t *, int); 

/*    FREE    */
void free_end_robots(room_t *, robot_t **);
void my_free_list(linked_list_t **);
void free_path(path_t *);
room_t * free_best_room(algo_t *, room_t *);
void free_path_list(linked_list_t *);

/*    UTILS    */
int mini_printf(int, const char *, ...);
int my_array_len(void **array);
int my_count_letter(char *str, char c);
void remove_comment(char *str);
linked_list_t *my_find_node(linked_list_t *list, void *data);
void add_to_end(linked_list_t **list_ptr, void *data);
void add_to_beggining(linked_list_t **list_ptr, void *data);
void my_delete_nodes(linked_list_t **list_ptr, void *data);
void *return_and_free(maze_t *maze, linked_list_t **file_content, char **line);
room_t *add_room_to_list(maze_t *maze, char *name, int posx, int posy);

#endif /* AMAZED_H_ */
