/*
** EPITECH PROJECT, 2024
** B-CPE-101-LIL-1-1-miniprintf-theophile.riffe
** File description:
** utilities
*/

#include "my_printf.h"

void print_char(va_list args, buffer_t *buff)
{
    printf_putchar(va_arg(args, int), buff);
}

void print_string(va_list args, buffer_t *buff)
{
    printf_putstr(va_arg(args, char *), buff);
}

void print_int(va_list args, buffer_t *buff)
{
    printf_putnbr(va_arg(args, int), buff);
}

void print_mudulo(__attribute__((unused))va_list args, buffer_t *buff)
{
    printf_putchar('%', buff);
}
