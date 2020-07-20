#include "ush.h"

static void check_delname(char *name, int *status) {
    if (!(*status))
        if ((*status = mx_match_search(name, "=")))
            mx_print_error_env(0, 0, name);
}

static void delete_name(char **name) {
    unsetenv(*name);
    mx_strdel(name);
}

static char *get_flag_arg(char **arr, int *ch_index, int *status, int *i) {
    if (arr[0][(*ch_index) + 1] == '\0') {
        if (arr[1] == NULL) {
            *status = mx_print_error_env(arr[0][*ch_index], 1, NULL);
        }
        else {
            *ch_index = -1;
            (*i)++;
            return mx_strdup(arr[1]);
        }
    }
    else {
        int step = *ch_index + 1;

        *ch_index = -1;
        return mx_strdup(arr[0] + step);
    }
    return NULL;
}

static int flags_finding(char **arr,  char **path, int *i) {
    int status = 0;

    for (int j = 0; arr[0][j]; j++) {
        if (arr[0][j] == 'P') {
            mx_strdel(path);
            *path = get_flag_arg(arr, &j, &status, i);
        }
        else if (arr[0][j] == 'u') {
            char *delname = get_flag_arg(arr, &j, &status, i);
            check_delname(delname, &status);
            delete_name(&delname);
        }
        else if (arr[0][j] != 'i' && arr[0][j] != '-')
            return mx_print_error_env(arr[0][j], 2, NULL);
        if (status || j == -1)
            break;
    }
    return status;
}

int mx_flags_handler_env(char **argv, int *i, char **path) {
    int res = 0;

    for (*i = 1; argv[*i] != NULL && !res; (*i)++) {
        if (argv[*i][0] == '-' && strcmp(argv[*i], "--") != 0) {
            if (mx_match_search(argv[*i], MX_ENV_I))
                mx_clearenv();
            res = flags_finding(&argv[*i], path, i);
        }
        else {
            if (strcmp(argv[*i], "--") == 0)
                (*i)--;
            break;
        }
    }
    return res;
}
