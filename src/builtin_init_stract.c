#include "ush.h"

void mx_init (t_app *pwd) {
    pwd->home = getenv("HOME");
    pwd->pwd_l = mx_strdup(getenv("PWD"));
    pwd->old_pwd_l = mx_strdup(pwd->pwd_l);
    pwd->pwd_p = getwd(NULL);
    pwd->old_pwd_p = mx_strdup(pwd->pwd_p);
}

