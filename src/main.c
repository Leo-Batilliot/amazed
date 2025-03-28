/*
** EPITECH PROJECT, 2024
** c_proj_template
** File description:
** main
*/

#include "amaze.h"
#include "my_printf.h"
#include "my_strings.h"
#include "my_numbers.h"
#include "my_lists.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    list_t *head = NULL;

    (void)av;
    if (ac > 3)
        return 84;
    if (do_parse(&head) == 84)
        return 84;
    return 0;
}
