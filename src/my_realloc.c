/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** realloc
*/

// #include "amaze.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void my_memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr = NULL;

    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL)
        return malloc(new_size);
    if (old_size == new_size)
        return ptr;
    new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL;
    if (new_size > old_size)
        my_memcpy(new_ptr, ptr, old_size);
    else
        my_memcpy(new_ptr, ptr, new_size);
    free(ptr);
    return new_ptr;
}
