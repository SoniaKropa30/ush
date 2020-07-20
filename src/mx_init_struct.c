#include "ush.h"

char **mx_alias_arr() {
    char **arr = (char**)malloc(sizeof(char*) * 1);

    arr[0] = NULL;
    return arr;
}

void mx_init_struct(t_st *st, char **env) {
    char *tmp = NULL;
    int n = 0;

    st->env = env;
    st->alias = mx_alias_arr();
    st->status = 0;
    tmp = getenv("SHELL");
    if (mx_strcmp(tmp, "./ush") != 0) {
        setenv("SHELL", "./ush", 1);
        setenv("SHLVL", "1", 1);
    }
    else {
        tmp = getenv("SHLVL");
        n = atoi(tmp) + 1;
        sprintf(tmp, "%d", n);
        printf("%s\n", tmp);
        setenv("SHLVL", tmp, 1);
    }
}
