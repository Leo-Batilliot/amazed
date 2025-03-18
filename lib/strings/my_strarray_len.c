/*
** EPITECH PROJECT, 2025
** test_minishell [WSL: fedora]
** File description:
** my_strarray_len
*/

#include "my_strings.h"

int
my_strarray_len(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i]; i++);
    return i;
}
