/*
** EPITECH PROJECT, 2024
** my_libc
** File description:
** my_puterr
*/

#include <unistd.h>
#include <stddef.h>
#include "my_io.h"
#include "my_strings.h"

void my_puterr(char const *str)
{
    if (str == NULL)
        return;
    write(2, str, my_strlen(str));
}
