/*
** EPITECH PROJECT, 2024
** my_libc
** File description:
** my_putstr
*/

#include "my_printf.h"

void printf_putstr(char const *str, buffer_t *buff)
{
    if (str == NULL)
        return;
    for (int i = 0; str[i] != '\0'; i++)
        printf_putchar(str[i], buff);
}
