/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** array_len
*/

int my_array_len(void **array)
{
    int res = 0;

    if (!array)
        return res;
    for (; array[res]; res++);
    return res;
}
