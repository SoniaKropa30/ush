#include "ush.h"
int mx_swap_pwd (char *ch, char *argv[], t_app *app) {

    if (ch) {
        if (chdir(ch) < 0) {
            fprintf(stderr,
                    "cd: no such file or directory: %s\n", argv[app->cur_arg]);
            return -1;
        }
        app->old_pwd_p = app->pwd_p;
        app->old_pwd_l = app->pwd_l == NULL ? app->pwd_ll : app->pwd_l;
        app->pwd_l = ch;
        app->pwd_p = getwd(NULL);
        setenv("PWD", app->pwd_l, 1);

        return 0;
    }
    else
        return -1;
}


