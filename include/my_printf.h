/*
** EPITECH PROJECT, 2024
** B-CPE-101-LIL-1-1-miniprintf-theophile.riffe
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include <unistd.h>
    #include <stdarg.h>
    #include <limits.h>

typedef struct buffer_s {
    char buffer[1024];
    int pos;
    int len;
} buffer_t;

typedef struct printf_s {
    char c;
    void (*func)(va_list, buffer_t *);
} printf_t;

void printf_putchar(char c, buffer_t *buff);
void printf_putstr(char const *str, buffer_t *buff);
int printf_putnbr(int n, buffer_t *buff);
int my_printf(char const *format, ...);

void print_char(va_list args, buffer_t *buff);
void print_string(va_list args, buffer_t *buff);
void print_int(va_list args, buffer_t *buff);
void print_mudulo(va_list args, buffer_t *buff);

#endif /* !MY_H_ */
