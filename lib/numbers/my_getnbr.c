/*
** EPITECH PROJECT, 2024
** my_lib
** File description:
** my_getnbr
*/

#include <limits.h>
#include "my_numbers.h"

int my_getnbr(char const *str)
{
    long result = 0;
    int digit = 0;
    int sign = 1;
    int i = 0;

    for (; str[i] == '-' || str[i] == '+'; i++)
        if (str[i] == '-')
            sign = - sign;
    for (; str[i] >= '0' && str[i] <= '9'; i++){
        digit = str[i] - '0';
        if (sign == 1 && (result > (INT_MAX - digit) / 10))
            return 0;
        if (sign == -1 && (- result < (INT_MIN + digit) / 10))
            return 0;
        result = result * 10 + digit;
    }
    return (int)(result * sign);
}
