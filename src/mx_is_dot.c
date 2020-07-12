#include "ush.h"

static bool dd_slesh(char *argv) {
    if (argv[0] == '.' && argv[1] == '.' && argv[2] == '/')
        return true;
    else
        return false;
}

static int check_ddslesh(char *argv, t_app *app) {
    char **arr_dot = NULL;

    arr_dot = mx_strsplit(argv, '/');
    for(int j = 0; arr_dot[j] != NULL; j++) {
        if (strcmp("..", arr_dot[j]) != 0) {
            app->dot_dir = 0;
            fprintf(stderr,
                    "cd: no such file or directory: %s\n", argv);
            return - 1;
        }
        else {
            app->dot_dir++;
            app->dd_slesh = 1;
        }
    }
    return 0;
}

static int calculate_dot(char *argv, t_app *app) {
    int i = 0;

    while (argv[i]) {
        if (argv[i] == '.' && i < 6) {
            i++;
            app->dot_dir++;
        }
        else {
            app->dot_dir = 0;
            fprintf(stderr,
                    "dottt ! cd: no such file or directory: %s\n", argv);
            return -1;
        }
    }
    return 0;
}

int mx_is_dot(char *argv, t_app *app) {
    app->dot_dir = 0;
    int res = 0;

    if(argv[0] == '.' && !argv[1])
        return 0;
    else {
        if(dd_slesh(argv)) {
            res = check_ddslesh(argv, app);
            return res;
        }
        else {
            res = calculate_dot(argv, app);
            return res;
        }
    }
}

