/*
** EPITECH PROJECT, 2025
** amazed
** File description:
** main
*/
#include "bonus.h"

static int print_help(char *filepath)
{
    struct stat st;
    char *buffer = NULL;
    FILE *file = NULL;

    if (stat(filepath, &st) != 0)
        return dprintf(2, "Erreur stat : fichier %s\n", filepath);
    file = fopen(filepath, "r");
    if (!file)
        return dprintf(2, "Erreur ouverture : fichier %s\n", filepath);
    buffer = malloc(st.st_size + 1);
    if (!buffer) {
        dprintf(2, "Erreur malloc : fichier %s\n", filepath);
        return fclose(file);
    }
    fread(buffer, 1, st.st_size, file);
    buffer[st.st_size] = '\0';
    printf("%s", buffer);
    free(buffer);
    fclose(file);
    return 0;
}

static int change_scene(sfRenderWindow *window, int scene)
{
    if (scene == 84)
        return 0;
    if (scene == 0)
        return change_scene(window, menu_main(window));
    if (scene == 1)
        return change_scene(window, simulation_main(window));
    return -1;
}


static sfRenderWindow *create_window(void)
{
    sfVideoMode desktop;
    sfVector2i position;
    sfContextSettings settings = {24, 8, 4, 2, 0, 0, 0};
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window = sfRenderWindow_create(
        mode, "AMAZED BONUS", sfClose | sfResize, &settings);

    if (!window) {
        dprintf(2, "Window creation failed.\n");
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(window, 60);
    desktop = sfVideoMode_getDesktopMode();
    position.x = (desktop.width - 1920) / 2;
    position.y = (desktop.height - 1080) / 2;
    sfRenderWindow_setPosition(window, position);
    return window;
}

int main(int ac, char **av)
{
    sfRenderWindow *window;

    if (ac == 2 && !strcmp(av[1], "-h"))
        return print_help("src/assets/helper.txt");
    if (ac > 1)
        return 0;
    if (!getenv("DISPLAY")) {
        fprintf(stderr, "Please provide a graphical environment.\n");
        return 0;
    }
    window = create_window();
    if (!window)
        return 84;
    srand(time(NULL));
    change_scene(window, 0);
    sfRenderWindow_close(window);
    sfRenderWindow_destroy(window);
    return 0;
}
