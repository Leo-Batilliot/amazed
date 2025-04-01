/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** amaze
*/

#ifndef AMAZE_H_
    #define AMAZE_H_

    #include "my_lists.h"

/* Alloc wrappers */
int link_node(char **, list_t **);
void *malloc(size_t size);
void *my_realloc(void *, size_t, size_t);
void my_memcpy(void *, const void *, size_t);
void free(void *);

int do_parse(list_t **);

#endif /* !AMAZE_H_ */
