/*
** EPITECH PROJECT, 2024
** my_libc
** File description:
** my_strchr
*/

#include "my_strings.h"

#include <stddef.h>

char *my_strchr(char *str, char c)
{
    int i = 0;

    if (!str)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] == c)
            return &str[i];
        i++;
    }
    return NULL;
}

char *my_strrchr(char *str, char c)
{
    int i = my_strlen(str);

    if (i < 0)
        return NULL;
    while (i >= 0) {
        if (str[i] == c)
            return &str[i];
        i--;
    }
    return NULL;
}

char *my_strnchr(char *str, char c, int n)
{
    int i = 0;
    int count = 0;

    if (!str)
        return NULL;
    while (str[i] != '\0') {
        if (str[i] == c)
            count++;
        if (count == n)
            return &str[i];
        i++;
    }
    return NULL;
}
