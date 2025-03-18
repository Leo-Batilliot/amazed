/*
** EPITECH PROJECT, 2024
** my_libc
** File description:
** strlen clone
*/

#include "my_strings.h"

int my_strlen(char const *str)
{
    int len = 0;

    if (!str)
        return -1;
    while (str[len] != '\0')
        len++;
    return len;
}
