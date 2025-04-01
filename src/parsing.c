/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** parsing
*/

#include "my_printf.h"
#include "my_lists.h"
#include "my_strings.h"
#include "my_numbers.h"
#include "amaze.h"

static int handle_start_end(char **array, int *is_start, int *is_end)
{
    if (!my_strcmp(array[0], "##start")) {
        my_printf("##start\n");
        *is_start = 1;
        return 1;
    }
    if (!my_strcmp(array[0], "##end")) {
        my_printf("##end\n");
        *is_end = 1;
        return 1;
    }
    return 0;
}

int print_data(int n, char **array, int param)
{
    if (!array)
        return 84;
    for (int i = 0; i < n; i++)
        if (!array[i])
            return 84;
    for (int i = 0; i < n; i++) {
        if (!my_str_isnum(array[i]))
            return 84;
        my_printf("%i", my_getnbr(array[i]));
        if (array[i + 1] && param == 0)
            my_printf(" ");
        if (array[i + 1] && param == 1)
            my_printf("-");
    }
    my_printf("\n");
    return 0;
}

static int process(list_t **head, char **array, int *is_start, int *is_end)
{
    if (my_strarray_len(array) == 3) {
        if (print_data(3, array, 0) == 84)
            return 84;
        append_node(head, array, (*is_start), (*is_end));
        (*is_end) = 0;
        (*is_start) = 0;
    }
    return 0;
}

static int process_tunnels(list_t **head, char **array, int *print_tunnels)
{
    char **new_array = NULL;

    if (my_strarray_len(array) == 1) {
        if (*print_tunnels == 0) {
            my_printf("#tunnels\n");
            *print_tunnels = 1;
        }
        new_array = split_string(array[0], "-");
        if (print_data(2, new_array, 1) == 84) {
            my_free_word_array(new_array);
            return 84;
        }
        if (link_node(new_array, head) == 1) {
            my_free_word_array(new_array);
            return 1;
        }
    }
    return 0;
}

int parse_first(char *line, char ***array, int count)
{
    line[my_strlen(line) - 1] = '\0';
    (*array) = split_string(line, " \t");
    if (!(*array) || !(*array)[0])
        return 1;
    if (count == 0) {
        my_printf("#number_of_robots\n%i\n", my_getnbr(line));
        my_printf("#rooms\n");
        return 1;
    }
    return 0;
}

static int handle_room(list_t **head, char **array,
    int *is_start, int *is_end)
{
    if (handle_start_end(array, is_start, is_end) == 1)
        return 1;
    if (process(head, array, is_start, is_end) == 84)
        return 84;
    return 0;
}

int free_and_return(char *line, int ex)
{
    free(line);
    return ex;
}

int do_parse(list_t **head)
{
    char *line = NULL;
    char **array = NULL;
    size_t len = 0;
    int flags[4] = {0};

    for (int count = 0; getline(&line, &len, stdin) != -1; count++) {
        if (parse_first(line, &array, count) == 1)
            continue;
        flags[3] = handle_room(head, array, &flags[0], &flags[1]);
        if (flags[3] == 84)
            return free_and_return(line, 84);
        if (flags[3] == 1)
            continue;
        flags[3] = process_tunnels(head, array, &flags[2]);
        if (flags[3] == 84)
            return free_and_return(line, 84);
        if (flags[3] == 1)
            continue;
    }
    return free_and_return(line, 0);
}
