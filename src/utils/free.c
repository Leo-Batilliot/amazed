/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** free
*/
#include "amazed.h"
#include <stddef.h>
#include <stdlib.h>

int my_free(void *to_free)
{
    if (to_free)
        free(to_free);
    return 0;
}

int free_array(void **array)
{
    if (!array)
        return 0;
    for (int i = 0; array[i]; i += my_free(array[i]) + 1);
    return my_free(array);
}
