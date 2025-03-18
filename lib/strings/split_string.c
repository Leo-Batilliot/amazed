/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday08-theophile.riffe
** File description:
** str_to_word_array
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "my_strings.h"

static int isdelim(char c, char const *delim)
{
    if (c == '\0')
        return 1;
    for (int i = 0; delim[i] != '\0'; i++)
        if (c == delim[i])
            return 1;
    return 0;
}

static int count_words(char const *str, char const *delim)
{
    int wcount = 0;
    int i = 0;
    int is_word = 0;

    if (str == NULL)
        return 0;
    while (str[i] != '\0') {
        if (!isdelim(str[i], delim) && is_word == 0){
            is_word = 1;
            wcount++;
        }
        if (isdelim(str[i], delim))
            is_word = 0;
        i++;
    }
    return wcount;
}

void
skip(char const *str, int *i, char const *delim, bool skip_delim)
{
    if (skip_delim)
        while (isdelim(str[*i], delim))
            (*i) += 1;
    else
        while (!isdelim(str[*i], delim))
            (*i) += 1;
}

char **split_string(char const *str, char const *delim)
{
    int wcount = count_words(str, delim);
    char **tab = malloc(sizeof(char *) * (wcount + 1));
    int i = 0;
    int start = 0;

    if (tab == NULL)
        return NULL;
    for (int j = 0; j < wcount; j++){
        skip(str, &i, delim, true);
        start = i;
        skip(str, &i, delim, false);
        tab[j] = malloc(i - start + 1);
        if (tab[j]) {
            my_strncpy(tab[j], str + start, i - start);
            tab[j][i - start] = '\0';
        }
    }
    tab[wcount] = NULL;
    return tab;
}
