/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** my_sprintf
*/

#include "my_printf.h"
#include "my_strings.h"

int my_sprintf(char *str, char const *format, ...)
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
    my_strcpy(str, buff.buffer);
    return buff.len;
}
