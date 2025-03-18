/*
** EPITECH PROJECT, 2024
** myprintf
** File description:
** printf_tab
*/

#include <stddef.h>
#include "my_printf.h"

void printf_tab(char **tab, buffer_t *buff)
{
    format_t zero = {0, 0, -1, 0};

    for (int i = 0; tab[i] != NULL; i++){
        printf_putstr(tab[i], buff, &zero);
        printf_putchar('\n', buff);
    }
}
