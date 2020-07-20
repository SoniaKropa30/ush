#include "ush.h"

static void check_unset_path(char *argv[], t_app *app) {
    for(int i = 0; argv[i] != NULL; i++) {
        if(mx_strcmp(argv[i], "PATH") == 0)
            app->env_path_deleted = 1;
    }
}

int mx_builtin_unset(t_cmd *cmd, t_app *app) {
    int res = EXIT_SUCCESS;

    check_unset_path(cmd->argv, app);
    if (cmd->argc < 2) {
        fprintf(stderr, "unset: not enough arguments\n");
        return EXIT_FAILURE;
    }
    for (int i = 1; cmd->argv[i] != NULL; i++) {
        if (unsetenv(cmd->argv[i]) != -1
            && mx_match_search(cmd->argv[i], MX_UNSET_ARG))
                mx_env_del_var(cmd->argv[i], &app->vars);
        else {
            fprintf(stderr, "unset: %s: invalid parameter name\n",
                    cmd->argv[i]);
            res = EXIT_FAILURE;
        }
    }
    return res;
}

