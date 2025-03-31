/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** realloc
*/

#include "amaze.h"
#include <stdlib.h>

void my_memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
}

void *my_realloc(void *ptr, size_t new_size)
{
    size_t *old_size_ptr = NULL;
    size_t old_size = 0;
    size_t *new_ptr = NULL;
    void *new_data_ptr = NULL;

    if (!ptr)
        return malloc(new_size);
    old_size_ptr = (size_t *)ptr - 1;
    old_size = *old_size_ptr;
    new_ptr = malloc(new_size + sizeof(size_t));
    if (!new_ptr)
        return NULL;
    *new_ptr = new_size;
    new_data_ptr = (void *)(new_ptr + 1);
    if (old_size < new_size)
        my_memcpy(new_data_ptr, ptr, old_size);
    else
        my_memcpy(new_data_ptr, ptr, new_size);
    free(old_size_ptr);
    return new_data_ptr;
}

void *my_malloc(size_t size)
{
    size_t *ptr = malloc(size + sizeof(size_t));

    if (!ptr)
        return NULL;
    *ptr = size;
    return (void *)(ptr + 1);
}

void my_free(void *ptr)
{
    size_t *size_ptr = NULL;

    if (!ptr)
        return;
    size_ptr = (size_t *)ptr - 1;
    free(size_ptr);
}
