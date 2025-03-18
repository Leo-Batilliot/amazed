/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_fprintf
*/

#include "my_printf.h"

int my_dprintf(int fd, char const *format, ...)
{
    va_list args;
    buffer_t buff = {{0}, 0, 0};
    format_t spec = {0, 0, -1, 0};

    va_start(args, format);
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            parse_format(format, &i, &spec, args);
            manage_specifiers(format[i], args, &buff, &spec);
        } else {
            printf_putchar(format[i], &buff);
        }
    }
    va_end(args);
    put_buffer(&buff, fd);
    return buff.len;
}
