#include "ush.h"

int mx_print_error_env(char ch, int err, char *str) {
    if (err == 0)
        fprintf(stderr, "env: unsetenv %s: Invalid argument\n", str);
    else {
        if (err == 1)
            fprintf(stderr, "env: option requires an argument -- %c\n", ch);
        else if (err == 2)
            fprintf(stderr, "env: bad option: -- %c\n", ch);
        fprintf(stderr, "usage: env [-i] [-P utilpath] [-u name]\n");
        fprintf(stderr, "           [name=value ...] [utility [argument ...]]\n");
    }
    return EXIT_FAILURE;
}

static void vars_handler_env(char **arr, int *i) {
    char *p = NULL;

    for (; arr[*i] && (p = strchr(arr[*i], '=')); (*i)++) {
        *p = '\0';
        setenv(arr[*i], p + 1, 1);
        *p = '=';
    }
}

int mx_env_builtin(char *argv[]) {
    int status = 0;
    int i = 0;
    char *path = NULL;
    char **env_copy = mx_environ_copy();

    if (!(status = mx_flags_handler_env(argv, &i, &path))) {
        vars_handler_env(argv, &i);
        if (argv[i] == NULL) {
            mx_print_env();
        }
        else
            status = mx_exec_env(&argv[i], path);
    }
    mx_env_fill(env_copy);
    mx_del_strarr(&env_copy);
    mx_strdel(&path);
    return status;
}
