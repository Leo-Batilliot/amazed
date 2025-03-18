/*
** EPITECH PROJECT, 2024
** B-CPE-101-LIL-1-1-miniprintf-theophile.riffe
** File description:
** mini_printf
*/

#include "my_printf.h"

const printf_t SPECIFIERS[] = {
    {'c', &print_char},
    {'s', &print_string},
    {'d', &print_int},
    {'i', &print_int},
    {'%', &print_mudulo},
    {0, NULL}
};

static void manage_specifiers(char c, va_list args, buffer_t *buff)
{
    for (int i = 0; SPECIFIERS[i].c != '\0'; i++) {
        if (c == SPECIFIERS[i].c) {
            SPECIFIERS[i].func(args, buff);
            return;
        }
    }
    printf_putchar('%', buff);
    printf_putchar(c, buff);
}

void put_buffer(buffer_t *buff)
{
    if (buff->pos > 0) {
        write(1, buff->buffer, buff->pos);
        buff->pos = 0;
    }
}

int my_printf(char const *format, ...)
{
    va_list args;
    buffer_t buff = {{0}, 0, 0};

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            manage_specifiers(format[i], args, &buff);
        } else {
            printf_putchar(format[i], &buff);
        }
    }
    va_end(args);
    put_buffer(&buff);
    return buff.len;
}
