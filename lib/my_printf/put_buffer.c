/*
** EPITECH PROJECT, 2024
** my_printf
** File description:
** put_buffer
*/

#include <unistd.h>
#include "my_printf.h"

void put_buffer(buffer_t *buff, int fd)
{
    if (buff->pos > 0) {
        write(fd, buff->buffer, buff->pos);
        buff->pos = 0;
    }
}
