/*
** EPITECH PROJECT, 2025
** bonus
** File description:
** main
*/

#include "bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <strings.h>
#include <math.h>

static int update_scale(sim_t *sim, float max_x, float max_y)
{
    float scale_x = (1920.0f - 200.0f) / max_x;
    float scale_y = (1080.0f - 200.0f) / max_y;

    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next) {
        tmp->pos.x = (int)(tmp->pos.x * scale_x + 100);
        tmp->pos.y = (int)(tmp->pos.y * scale_y + 100);
    }
    return 0;
}

int get_min_max(sim_t *sim)
{
    float min_x = sim->list->pos.x;
    float max_x = sim->list->pos.x;
    float min_y = sim->list->pos.y;
    float max_y = sim->list->pos.y;

    for (rooms_t *tmp = sim->list; tmp; tmp = tmp->next) {
        if (tmp->pos.x < min_x)
            min_x = tmp->pos.x;
        if (tmp->pos.x > max_x)
            max_x = tmp->pos.x;
        if (tmp->pos.y < min_y)
            min_y = tmp->pos.y;
        if (tmp->pos.y > max_y)
            max_y = tmp->pos.y;
    }
    max_x -= min_x;
    max_y -= min_y;
    update_scale(sim, max_x, max_y);
    return 0;
}

round_t *find_node(robot_t *robot, int count)
{
    int i = 0;
    round_t *cur = robot->positions;

    while (cur != NULL && i < count) {
        cur = cur->next;
        i++;
    }
    return cur;
}

FILE *try_to_open(void)
{
    FILE *fd = NULL;
    char cmd[256];

    char *str = "./amazed < bonus/test_files/program_input.txt > ";
    snprintf(cmd, sizeof(cmd),
        "%stemp && mv temp bonus/test_files/program_input.txt", str);
    if (system(cmd)) {
        printf("invalid file\n");
        return NULL;
    }
    fd = fopen("bonus/test_files/program_input.txt", "r");
    if (!fd) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    return fd;
}

int simulation_main(sfRenderWindow *window)
{
    sim_t *sim = NULL;
    FILE *fd = NULL;
    int res = 0;

    sim = init_sim();
    if (!sim)
        return 84;
    fd = try_to_open();
    if (!fd)
        return 84;
    parse_file(fd, sim);
    res = main_loop(sim, window);
    free_sim(sim);
    return res;
}