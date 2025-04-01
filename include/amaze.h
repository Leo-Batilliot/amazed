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
void *my_realloc(void *, size_t, size_t);
void my_memcpy(void *, const void *, size_t);

int do_parse(list_t **);

#endif /* !AMAZE_H_ */
