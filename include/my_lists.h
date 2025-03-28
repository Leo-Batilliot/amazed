/*
** EPITECH PROJECT, 2024
** c_lists
** File description:
** lists
*/

#ifndef CLISTS_H
    #define CLISTS_H

    #include <stdlib.h>
    #include <stdio.h>

/*
** The structure, and especially its data
** is just an example. You should modify it
** to fit your needs.
**
** The same applies for the functions below,
** you should modify the comparisons and the
** data type to fit your needs.
*/

typedef struct list_s {
    int is_start;
    int is_end;
    int this_index;
    int num;
    int index[2];
    struct list_s **tab;
    struct list_s *next;
} list_t;

list_t *create_node(char **, int, int);
list_t *reverse_list(list_t *);
// list_t *find_node(list_t *, void const *,
//     int (*cmp)(void const *, void const *));
list_t *find_node(list_t *head, int to_cmd);

int list_size(list_t *);

void merge_sort(list_t **, int (*cmp)(void const *, void const *));
void add_to_top(list_t **, char **);
void append_node(list_t **, char **, int, int);
void insert_node_at(list_t **, void *, int index);
void free_list(list_t **, void (*free_data)(void *));
void remove_node(list_t **, void const *, void (*free_data)(void *),
    int (*cmp)(void const *, void const *));

#endif
