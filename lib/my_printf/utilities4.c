/*
** EPITECH PROJECT, 2024
** myprintf
** File description:
** utilities4
*/

#include "my_printf.h"

void print_tab(va_list args, buffer_t *buff,
    __attribute__((unused))format_t *flags)
{
    printf_tab(va_arg(args, char **), buff);
}
