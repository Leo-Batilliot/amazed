/*
** EPITECH PROJECT, 2024
** my_lib
** File description:
** my_put_nbr
*/

#include "my_printf.h"

int printf_putnbr(int n, buffer_t *buff)
{
    if (n == INT_MIN) {
        printf_putchar('-', buff);
        printf_putchar('2', buff);
        n = 147483648;
    } else if (n < 0) {
        printf_putchar('-', buff);
        n = -n;
    }
    if (n >= 10)
        printf_putnbr(n / 10, buff);
    printf_putchar(n % 10 + '0', buff);
    return 0;
}
