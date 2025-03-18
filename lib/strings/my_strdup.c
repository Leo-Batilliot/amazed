/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday08-theophile.riffe
** File description:
** my_strdup
*/

#include <stdlib.h>
#include <stddef.h>
#include "my_strings.h"

char *my_strndup(char const *src, int n)
{
    char *new = NULL;
    int len = my_strlen(src);

    if (n > len)
        n = len;
    new = malloc(sizeof(char) * (n + 1));
    if (new == NULL)
        return NULL;
    for (int i = 0; i < n; i++)
        new[i] = src[i];
    new[n] = '\0';
    return new;
}

char *my_strdup(char const *src)
{
    int len = 0;
    char *new = NULL;
    int i = 0;

    if (!src)
        return NULL;
    len = my_strlen(src);
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return NULL;
    for (; src[i] != '\0'; i++)
        new[i] = src[i];
    new[i] = '\0';
    return new;
}
