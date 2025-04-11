/*
** EPITECH PROJECT, 2025
** G-ING-200-LIL-2-1-myworld-gabin.wilson
** File description:
** arrays
*/

#include "bonus.h"

void free_array_until(char **array, int max)
{
    if (!array)
        return;
    for (int i = 0; i < max; i++) {
        if (array[i])
            free(array[i]);
    }
    free(array);
}

int my_array_len(char **array)
{
    int i = 0;

    if (!array)
        return i;
    for (; array[i]; i++);
    return i;
}
